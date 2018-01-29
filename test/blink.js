// test.js
const LEDStrip = require('../index.js');
const led = new LEDStrip();

const colors = {
  info: '#209cFe',
  success: '#38F87C',
  warning: '#F3B201',
  error: '#F34541',
};

led.blink(colors.info);

setTimeout(() => {
  led.turnOff();
}, 10000)

const release = () => {
  led.release();
  process.exit();
}

process.on('exit', release);
// process.on('SIGINT', release);
// process.on('SIGTERM', release);
