// test.js
const LEDStrip = require('../index.js');
const led = new LEDStrip();

const colors = {
  info: '#209cFe',
  success: '#38F87C',
  warning: '#F3B201',
  error: '#F34541',
};

const colorArray = Object.keys(colors);

const renderColors = (idx) => {
  if (idx >= 4) {
    return;
  } else {
    const color = colors[colorArray[idx]];
    led.turnOn(color);
    setTimeout(() => renderColors(idx+1), 1000);
  }
}

renderColors(0);

const release = () => {
  led.release();
  process.exit();
}

process.on('exit', release);
// process.on('SIGINT', release);
// process.on('SIGTERM', release);
