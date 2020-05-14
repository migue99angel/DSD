var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash"};
var MongoClient = require('mongodb').MongoClient;
var MongoServer = require('mongodb').Server;

var LUM_ACTUAL = 50
var TEMP_ACTUAL = 25

var UMBRAL_TEMP = 30
var UMBRAL_LUM = 20 

var persiana = false  //false bajada - true subida 
var aireAcondicionado = false  //false apagado - true encendido
var agenteDomotico = true //Variable que apaga o enciende el agente domotico


function agente()
{
	if(agenteDomotico)
	{
		var mensajes = Array();

		if (TEMP_ACTUAL > UMBRAL_TEMP && !aireAcondicionado)
		{
			aireAcondicionado = true
			mensajes.push("El agente ha encendido el aire acondicionado porque la temperatura es muy alta\n");
		}
		else if (TEMP_ACTUAL < UMBRAL_TEMP && aireAcondicionado)
		{
			aireAcondicionado = false
			mensajes.push("El agente ha apagado el aire acondicionado porque la temperatura es inferior al umbral\n");
		}

		if (LUM_ACTUAL < UMBRAL_LUM && !persiana)
		{
			mensajes.push("El agente ha subido la persiana porque la luminosidad es inferior al umbral\n");
			persiana = true
		}

		if (TEMP_ACTUAL > UMBRAL_TEMP && LUM_ACTUAL > UMBRAL_LUM)
		{
			persiana = false
			mensajes.push("El agente ha bajado la persiana porque la temperatura y la luminosidad son muy altas\n");
		}
		
		return mensajes;
		
	}
}

var httpServer = http.createServer(
	function(request, response) {
		var uri = url.parse(request.url).pathname;
		if (uri=="/") uri = "/sensores.html";
		var fname = path.join(process.cwd(), uri);
		fs.exists(fname, function(exists) {
			if (exists) {
				fs.readFile(fname, function(err, data){
					if (!err) {
						var extension = path.extname(fname).split(".")[1];
						var mimeType = mimeTypes[extension];
						response.writeHead(200, mimeType);
						response.write(data);
						response.end();
					}
					else {
						response.writeHead(200, {"Content-Type": "text/plain"});
						response.write('Error de lectura en el fichero: '+uri);
						response.end();
					}
				});
			}
			else{
				while (uri.indexOf('/') == 0) uri = uri.slice(1);
				var params = uri.split("/");
				if (params.length >= 2) { //REST Request
					console.log("Peticion REST: "+uri);
					response.writeHead(200, {"Content-Type": "text/html"});
					response.end();
				}
				else {
					console.log("Peticion invalida: "+uri);
					response.writeHead(200, {"Content-Type": "text/plain"});
					response.write('404 Not Found\n');
					response.end();
				}
			}
		});		
	});


MongoClient.connect("mongodb://localhost:27017/", function(err, db){
	httpServer.listen(8080);
	console.log("Servicio HTTP iniciado");
	var io = socketio.listen(httpServer);
	var users = new Array();
	var dbo = db.db("pruebaBaseDatos");

	dbo.createCollection("registroCambios", function(err, collection){

	io.sockets.on('connection', function(u){
		users.push({address:u.request.connection.remoteAddress, port:u.request.connection.remotePort})
		console.log('New user from: '+u.request.connection.remoteAddress + ':' + u.request.connection.remotePort);
		
		u.emit('my-address', {host:u.request.connection.remoteAddress, port:u.request.connection.remotePort});

		io.emit('usuarios-activos',users);

		u.emit('valoresSensores', {
			temperatura: TEMP_ACTUAL,
			luminosidad: LUM_ACTUAL,
			estadoAireAcondicionado: aireAcondicionado,
			estadoPersiana: persiana,
			estadoAgenteDomotico: agenteDomotico,
			mensajesAgente : 'El agente no ha actuado todavía' 
		});

		u.on('Aire-Acondicionado',function(){
			aireAcondicionado = !aireAcondicionado;
			collection.insert({estadoAireAcondicionado: aireAcondicionado }, {safe:true}, function(err, result) {});
			actualizarValoresUsuarios();
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})

		u.on('persiana',function(){
			persiana = !persiana;
			collection.insert({estadoPersiana: persiana }, {safe:true}, function(err, result) {});
			actualizarValoresUsuarios();
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})

		u.on('valores-captados',function(data){
			if(data.sensor == 'temperatura')
			{
				TEMP_ACTUAL = data.valor;

			}else if(data.sensor == 'luminosidad')
			{
				LUM_ACTUAL = data.valor;
			}
			var mensajes = agente();
			actualizarValoresUsuarios(mensajes);
			collection.insert(data, {safe:true}, function(err, result) {});
			obtenerRegistro()
		})

		u.on('obtener-registro',function(data){
			obtenerRegistro(data);
		});


		u.on('estado-agente',function(){
			agenteDomotico = !agenteDomotico;
			var mensajes = agente();
			actualizarValoresUsuarios(mensajes);
		})


		u.on('disconnect',function(){
			console.log("El cliente "+u.request.connection.remoteAddress+" se va a desconectar");
			users = removeItemFromArr( users, {address:u.request.connection.remoteAddress, port:u.request.connection.remotePort} );
			io.emit('usuarios-activos',users);
		});


		function obtenerRegistro()
		{
			collection.find().toArray(function(err, results){
				io.emit('obtener-registro',results);
			});
		}


		});

		function removeItemFromArr ( arr, item ) {
			var i = -1;

			for(var j = 0; j < arr.length; j++)
				if(arr[j].port == item.port)
					i = j;

			if ( i != -1 ) {
				arr.splice( i, 1 );
			}

			return arr;
		}

		function actualizarValoresUsuarios(mensajes)
		{
			io.sockets.emit('valoresSensores', {
				temperatura: TEMP_ACTUAL,
				luminosidad: LUM_ACTUAL,
				estadoAireAcondicionado: aireAcondicionado,
				estadoPersiana: persiana,
				estadoAgenteDomotico: agenteDomotico,
				mensajesAgente : mensajes
			});
		}
	});
});

	

