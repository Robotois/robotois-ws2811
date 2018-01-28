const addon = require('./build/Release/addon');

/**
 * Converts a hx valuer to RGB value.
 * @param {int} hx The second argument.
 * @returns {Array} RBG Array string.
 */
const hexToRGB = function hexToRGB(hx) {
  const hex = hx.replace('#', '');
  return [
    parseInt(hex.substring(0, 2), 16),
    parseInt(hex.substring(2, 4), 16),
    parseInt(hex.substring(4, 6), 16),
  ];
};

// const colors = {
//   info: '#209cee',
//   success: '#23d160',
//   warning: '#ffdd57',
//   error: '#ff3860',
// };

function WS2811Module() {
  const selft = this;

  this.led = new addon.MyObject();
  this.ledStatus = false;
  this.ledColor = {
    red: 0,
    green: 0,
    blue: 0
  };
  this.blinkInterval = false;

  process.on('SIGINT', () => {
    selft.led.release();
  });

  process.on('SIGTERM', () => {
    selft.led.release();
  });
}

WS2811Module.prototype.turnOff = function turnOff() {
  this.rgb.ledOff();
  this.ledStatus = false;
};

WS2811Module.prototype.turnOnRGB = function (red, green, blue) {
  this.led.ledOn(red, green, blue);
  this.ledStatus = true;
}

WS2811Module.prototype.turnOn = function (hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.led.ledOn(rgbColor[0], rgbColor[1], rgbColor[2]);
  this.ledStatus = true;
}

WS2811Module.prototype.blink = function blink(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.ledColor.red = rgbColor[0];
  this.ledColor.green = rgbColor[1];
  this.ledColor.blue = rgbColor[2];
  if (!this.blinkInterval) {
    this.turnOnRGB(rgbColor[0], rgbColor[1], rgbColor[2]);
    this.blinkInterval = setInterval(() => {
      this.toggle();
    }, 500);
  }
}

WS2811Module.prototype.toggle = function toggle() {
  if (this.ledStatus) {
    this.turnOff();
  } else {
    this.turnOnRGB(this.ledColor.red, this.ledColor.red, this.ledColor.red);
  }
}

WS2811Module.prototype.release = function release() {
  clearInterval(this.blinkInterval);
  this.led.release();
};

module.exports = WS2811Module;
