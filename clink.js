var printf=require('printf');

function dec2bin(dec) {
		return (dec >>> 0).toString(2);
}



var clink=require("./clinkjs/build/Release/clink");
var a=clink.sd788t_connect(1);
if (!a) {
	console.log("Failed to connect :(");
	process.exit(1);
} 
console.log(a);
console.log("Connected to 788T");

var b=clink.sd788t_get_transport(a);
console.log("transport="+b);

var temp=clink.sd788t_get_temperature(a);
console.log("temp="+temp);

let pc=clink.sd788t_get_parameter_change_status(a);
console.log(pc.pc_transport_mode_change());

console.log("version="+pc.version);

//console.log("takeflags="+dec2bin(pc.takeflags));
console.log("parflags1="+dec2bin(pc.parflags1));
console.log("parflags2="+dec2bin(pc.parflags2));
console.log("parflags3="+dec2bin(pc.parflags3));


function foo() {
	setTimeout(foo,50);
	let tc=clink.sd788t_get_timecode(a);
	console.log(printf("tc=%02u:%02u:%02u:%02u",tc.gen.hours,tc.gen.minutes,tc.gen.seconds,tc.gen.frames));

}

foo();
