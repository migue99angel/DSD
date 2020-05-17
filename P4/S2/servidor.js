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
var HUM_ACTUAL = 50
var SUCIEDAD_ACTUAL = 0
var VIENTO_ACTUAL;

var UMBRAL_TEMP = 30
var UMBRAL_TEMP_MIN = 10
var UMBRAL_LUM = 20 
var UMBRAL_HUMEDAD = 20
var UMBRAL_SUCIEDAD = 20
var UMBRAL_VIENTO = 0

var persiana = false  //false bajada - true subida 
var aireAcondicionado = false  //false apagado - true encendido
var calefaccion = false //false apagado - true encendido
var robotAspirador = false	//false apagado - true encendido
var cerraduraInteligente = false	//false apagado - true encendido
var humidificador = false //false apagado - true encendido
var ventana = true //false cerrrada - true abierta
var agenteDomotico = true //Variable que apaga o enciende el agente domotico


function agente()
{
	if(agenteDomotico)
	{
		var mensajes = Array();
		var d = new Date();

		if(d.getHours() >= 22 && d.getMinutes() >= 30  && !cerraduraInteligente)
		{
			cerraduraInteligente = true;
			mensajes.push("El agente ha encendido la cerradura inteligente porque ha llegado la hora programada</br>");
		}

		if (TEMP_ACTUAL > UMBRAL_TEMP && !aireAcondicionado)
		{
			aireAcondicionado = true;
			mensajes.push("El agente ha encendido el aire acondicionado porque la temperatura es muy alta</br>");
			if(!humidificador)
			{
				humidificador = true;
				mensajes.push("El agente ha encendido el humidificador porque el aire acondicionado está en uso</br>");
			}
			if(calefaccion)
			{
				calefaccion = false;
				mensajes.push("El agente ha apagado la calefacción para evitar tener el aire acondicionado y la calefacción encendidos simultáneamente</br>");
			}
				
		}
		else if (TEMP_ACTUAL < UMBRAL_TEMP && TEMP_ACTUAL > UMBRAL_TEMP_MIN && aireAcondicionado)
		{
			aireAcondicionado = false;
			mensajes.push("El agente ha apagado el aire acondicionado porque la temperatura es inferior al umbral </br>");
		}

		if(TEMP_ACTUAL < UMBRAL_TEMP_MIN && !calefaccion)
		{
			calefaccion = true;
			mensajes.push("El agente ha encendido la calefacción porque hace frío </br>")
			if(aireAcondicionado)
			{
				aireAcondicionado = false;
				mensajes.push("El agente ha apagado el aire acondicionado para evitar tener el aire acondicionado y la calefacción encendidos simultáneamente</br>");
			}
				

		}else if (TEMP_ACTUAL > UMBRAL_TEMP_MIN && calefaccion)
		{
			calefaccion = false;
			mensajes.push("El agente ha apgado la calefacción porque ya no es necesaria </br>")
		}

		if((aireAcondicionado | calefaccion) && ventana)
		{
			ventana = false;
			mensajes.push("El agente ha cerrado la ventana porque hay algún dispositivo de control de temperatura en uso </br>");

		}else if (!aireAcondicionado && !calefaccion && !ventana && VIENTO_ACTUAL < UMBRAL_VIENTO)
		{
			ventana = true;
			mensajes.push("El agente ha abierto la ventana porque no hay ningún dispositivo de control de temperatura en uso </br>");
		}

		if(VIENTO_ACTUAL > UMBRAL_VIENTO && ventana)
		{
			ventana = false;
			mensajes.push("El agente ha cerrado la ventana porque la velocidad del viento es muy alta </br>");
		}

		if (LUM_ACTUAL < UMBRAL_LUM && !persiana)
		{
			mensajes.push("El agente ha subido la persiana porque la luminosidad es inferior al umbral </br>");
			persiana = true;
		}

		if (TEMP_ACTUAL > UMBRAL_TEMP && LUM_ACTUAL > UMBRAL_LUM && persiana)
		{
			persiana = false;
			mensajes.push("El agente ha bajado la persiana porque la temperatura y la luminosidad son muy altas </br>");
		}

		if(SUCIEDAD_ACTUAL > UMBRAL_SUCIEDAD && !robotAspirador)
		{
			robotAspirador = true;
			mensajes.push("Recoge lo que tengas por el suelo, se ha encendido el robot aspirador. ¡ Cuidado con los cables ! </br>");

		}else if (SUCIEDAD_ACTUAL < UMBRAL_SUCIEDAD && robotAspirador)
		{
			robotAspirador = false;
			mensajes.push("El robot aspirador a terminado, ¡ Recuerda vaciar el depósito ! </br>")
		}

		if(HUM_ACTUAL < UMBRAL_HUMEDAD && !humidificador)
		{
			humidificador = true;
			mensajes.push("El agente ha encendido el humidificador porque los niveles de humedad están por debajo del umbral </br>");

		} else if(HUM_ACTUAL > UMBRAL_HUMEDAD && humidificador && !aireAcondicionado)
		{
			humidificador = false;
			mensajes.push("El agente ha apagado el humidificador porque los niveles de humedad están por encima del umbral y el aire acondicionado está apagado </br>");
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
		users.push({address:u.request.connection.remoteAddress, port:u.request.connection.remotePort});		
		obtenerRegistro();

		io.emit('usuarios-activos',users);

		u.emit('valoresSensores', {
			temperatura: TEMP_ACTUAL,
			luminosidad: LUM_ACTUAL,
			humedad: HUM_ACTUAL,
			suciedad: SUCIEDAD_ACTUAL,
			viento: VIENTO_ACTUAL,
			estadoAireAcondicionado: aireAcondicionado,
			estadoPersiana: persiana,
			estadoAgenteDomotico: agenteDomotico,
			estadoCalefaccion: calefaccion,
			estadoAspirador: robotAspirador,
			estadoVentana: ventana,
			estadoHumidificador: humidificador, 
			estadoCerradura: cerraduraInteligente,
			mensajesAgente : 'El agente no ha actuado todavía' 
		});

		u.on('Aire-Acondicionado',function(){
			aireAcondicionado = !aireAcondicionado;
			var mensaje;
			if(aireAcondicionado) mensaje = 'El usuario ha encendido el aire acondicionado manualmente' 
			else mensaje = 'El usuario ha apagado el aire acondicionado manualmente'
			actualizarValoresUsuarios(mensaje);
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})

		u.on('persiana',function(){
			persiana = !persiana;
			if(persiana) mensaje = 'El usuario ha subido la persiana manualmente' 
			else mensaje = 'El usuario ha bajado la persiana manualmente'
			actualizarValoresUsuarios(mensaje);
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})

		u.on('ventana',function(){
			ventana = !ventana;
			if(ventana) mensaje = 'El usuario ha abierto la ventana manualmente' 
			else mensaje = 'El usuario ha cerrado la ventana manualmente'
			actualizarValoresUsuarios(mensaje);
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})

		u.on('aspirador',function(){
			robotAspirador = !robotAspirador;
			if(robotAspirador) mensaje = 'El usuario ha encendido el robot aspirador manualmente' 
			else mensaje = 'El usuario ha apagado el robot aspirador manualmente'
			actualizarValoresUsuarios(mensaje);
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})

		u.on('humidificador',function(){
			humidificador = !humidificador;
			if(humidificador) mensaje = 'El usuario ha encendido el humidificador manualmente' 
			else mensaje = 'El usuario ha apagado el humidificador manualmente'
			actualizarValoresUsuarios(mensaje);
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})


		u.on('calefaccion',function(){
			calefaccion = !calefaccion;
			if(calefaccion) mensaje = 'El usuario ha encendido la calefacción manualmente' 
			else mensaje = 'El usuario ha apagado la calefacción manualmente'
			actualizarValoresUsuarios(mensaje);
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})

		u.on('cerradura',function(){
			cerraduraInteligente = !cerraduraInteligente;
			if(cerraduraInteligente) mensaje = 'El usuario ha encendido la cerradura inteligente manualmente' 
			else mensaje = 'El usuario ha apagado la cerradura inteligente manualmente'
			actualizarValoresUsuarios(mensaje);
			obtenerRegistro() //Actualizamos el registro de la pagina de los sensores
		})


		u.on('valores-captados',function(data){
			if(data.sensor == 'temperatura')
			{
				TEMP_ACTUAL = data.valor;

			}else if(data.sensor == 'luminosidad')
			{
				LUM_ACTUAL = data.valor;

			}else if(data.sensor == 'suciedad')
			{
				SUCIEDAD_ACTUAL = data.valor;

			}else if(data.sensor == 'humedad')
			{
				HUM_ACTUAL = data.valor;
			}
			var mensajes = agente();
			actualizarValoresUsuarios(mensajes);
			collection.insert(data, {safe:true}, function(err, result) {});
			obtenerRegistro()
		})

		u.on('obtener-registro',function(){
			obtenerRegistro();
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
				humedad: HUM_ACTUAL,
				suciedad: SUCIEDAD_ACTUAL,
				viento: VIENTO_ACTUAL,
				estadoAireAcondicionado: aireAcondicionado,
				estadoPersiana: persiana,
				estadoAgenteDomotico: agenteDomotico,
				estadoCalefaccion: calefaccion,
				estadoAspirador: robotAspirador,
				estadoVentana: ventana,
				estadoHumidificador: humidificador,  
				estadoCerradura: cerraduraInteligente,
				mensajesAgente : mensajes
			});
		}


	var unirest = require("unirest");
	var req = unirest("GET", "https://community-open-weather-map.p.rapidapi.com/weather");
	
	function peticionREST()
	{
		req.query({
			"id": "2172797",
			"units": "%22metric%22 or %22imperial%22",
			"mode": "xml%2C html",
			"q": "Motril"
		});
	
		req.headers({
			"x-rapidapi-host": "community-open-weather-map.p.rapidapi.com",
			"x-rapidapi-key": "80654e5700mshd73d5e7ad6318d2p1e0fa8jsnc9321dd0b68f",
			"useQueryString": true
		});
	
	
		req.end(function (res) {
			if (res.error) throw new Error(res.error);
	
			VIENTO_ACTUAL = res.body.wind.speed;
			var mensajes = agente();
			actualizarValoresUsuarios(mensajes);
		});
	}
	
		setInterval(()=>peticionREST(),1000);

	});

});

	


