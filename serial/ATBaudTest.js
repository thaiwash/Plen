const raspi = require('raspi');
const Serial = require('raspi-serial').Serial;
 
var bauds = [
  110, 
  300,
  600, 
  1200, 
  2400, 
  4800, 
  9600, 
  14400, 
  19200, 
  38400, 
  57600, 
  115200, 
  128000, 
  256000
]

global.baudTest = 0

raspi.init(() => {
    
  function TestConnection(baudRate) {
    var serial = new Serial({"portId":"/dev/serial1",
      "baudRate": baudRate});
    serial.open(() => {
      serial.on('data', (data) => {
        process.stdout.write(data);
      });
      console.log("wrote AT")
      serial.write('AT');
      setTimeout(function() {
        console.log("wrote AT")
        serial.write('AT');
      }, 3000)
      setTimeout(function() {
        serial.close(function() {
          console.log("socket closed")
        })
      }, 9000)
    });
  }
  
  global.interval = setInterval(function() {
    var baudRate = bauds[baudTest]
    console.log("Testing baud " + baudRate)
    TestConnection(baudRate)  
    baudTest ++
    if (baudTest == bauds.length) {
      clearInterval(global.interval)
    }
  }, 10000)
});

