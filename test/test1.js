// test.js
const LEDStrip = require('../index.js');
const led = new LEDStrip();
// const obj = new addon.MyObject(10);

const colors = [
  { red: 200, green: 0, blue: 0 },
  { red: 0, green: 200, blue: 0 },
  { red: 0, green: 0, blue: 200 },
  { red: 100, green: 0, blue: 0 },
  { red: 0, green: 100, blue: 0 },
];

const renderColors = (idx) => {
  if (idx >= colors.length) {
    return;
  } else {
    led.turnOnRGB(colors[idx].red, colors[idx].green, colors[idx].blue);
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
