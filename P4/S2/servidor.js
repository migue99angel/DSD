var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash"};

var LUM_ACTUAL = 50
var TEMP_ACTUAL = 25

var UMBRAL_TEMP = 30
var UMBRAL_LUM = 20 

var persiana = false  //false bajada - true subida 
var aireAcondicionado = false  //false apagado - true encendido

function leerSensores(operacion, val1)
{
    if (operacion=="temperatura")
    {
		TEMP_ACTUAL = val1
        agente(operacion)
    }
    else if (operacion == "luminosidad")
    {
		LUM_ACTUAL = val1
        agente(operacion)
	}
	
	actualizarValoresUsuarios();
}

function agente(operacion)
{
    if (operacion=="temperatura")
    {
        if (TEMP_ACTUAL > UMBRAL_TEMP)
        {
            aireAcondicionado = true
        }
        else
        {
            aireAcondicionado = false

        }
    } else if (operacion == "luminosidad")
    {

        if (LUM_ACTUAL < UMBRAL_LUM)
        {
            persiana = false
        }
        else if (LUM_ACTUAL > UMBRAL_LUM)
        {
            persiana = true
        }
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
					var val1 = parseFloat(params[1]);
					leerSensores(params[0], val1);
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
	}
);



console.log("Servicio HTTP iniciado");
var io = socketio.listen(httpServer);
var users = new Array();
io.sockets.on('connection', function(u){
	users.push({address:u.request.connection.remoteAddress, port:u.request.connection.remotePort})
	console.log('New user from: '+u.request.connection.remoteAddress + ':' + u.request.connection.remotePort);

	u.emit('valoresSensores', {
		temperatura: TEMP_ACTUAL,
		luminosidad: LUM_ACTUAL,
		estadoAireAcondicionado: aireAcondicionado,
		estadoPersiana: persiana
	});

	u.on('disconnect',function(){
		console.log("El cliente "+u.request.connection.remoteAddress+" se va a desconectar");
	})
});

function actualizarValoresUsuarios()
{
	io.sockets.emit('valoresSensores', {
		temperatura: TEMP_ACTUAL,
		luminosidad: LUM_ACTUAL,
		estadoAireAcondicionado: aireAcondicionado,
		estadoPersiana: persiana
	});
}

httpServer.listen(8080);

