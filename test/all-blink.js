const LEDStrip = require('../index.js');
const led = new LEDStrip(16);

const colors = {
  primary: '#00d1b2',
  link: '#3273dc',
  info: '#209cee',
  success: '#23d160',
  warning: '#ffdd57',
  error: '#ff3860',
};

led.allBlink(colors.success);

setTimeout(() => {
  led.allOff();
}, 10000)

const release = () => {
  led.release();
  process.exit();
}

process.on('exit', release);
// process.on('SIGINT', release);
// process.on('SIGTERM', release);
