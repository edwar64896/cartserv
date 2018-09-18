var link = require ("./clinkjs/build/Release/clink");
var express = require("express");
var app = express();
//var server = require('http').Server(app);

var bodyParser = require("body-parser");
var routes = require("./routes/routes.js");

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true
}));

routes(app);

var server = app.listen(3001, function() {
    console.log("app running on port.", server.address().port);
});

var io = require('socket.io')(server);

io.on('connection', function(socket) {
	console.log("got connected");

	socket.on('tsport',(name, fn) => {
		console.log("tsport " + name);
		fn('hello!');
	});

});


io.on('connect', (socket) => {
	console.log('connected to sockets');
	socket.on('disconnect', () => {
		console.log('disconnected from transport');
	})
})

