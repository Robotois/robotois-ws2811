const LEDStrip = require('../');
const led = new LEDStrip(3);

const colors = {
  primary: '#00d1b2',
  link: '#3273dc',
  info: '#209cee',
  success: '#23d160',
  warning: '#ffdd57',
  error: '#ff3860',
};

const colorArray = Object.keys(colors);

const renderColors = (length, idx) => {
  if((idx + 1) > length) {
    return;
  }
  const color = colors[colorArray[idx]];
  led.allOn(color);
  setTimeout(() => renderColors(length, idx+1), 2000);
}

renderColors(colorArray.length, 0);

const release = () => {
  led.release();
  process.exit();
}

process.on('exit', release);
// process.on('SIGINT', release);
// process.on('SIGTERM', release);
