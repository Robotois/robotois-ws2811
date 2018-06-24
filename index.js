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

function WS2811Module(width = 1, height = 1, brightness = 192, gpioPin = 1) {
  const selft = this;

  this.led = new addon.MyObject(width, height, brightness, gpioPin);
  this.ledStatus = false;
  this.allStatus = false;
  this.ledColor = {
    red: 0,
    green: 0,
    blue: 0
  };
  this.allColor = {
    red: 0,
    green: 0,
    blue: 0
  }
  this.blinkInterval = false;
  this.allBlinkInterval = false;

  process.on('SIGINT', () => {
    selft.led.release();
  });

  process.on('SIGTERM', () => {
    selft.led.release();
  });
}

WS2811Module.prototype.ledOn = function ledOn(red, green, blue) {
  this.led.ledOn(red, green, blue);
  this.ledStatus = true;
}


WS2811Module.prototype.ledOff = function ledOff() {
  this.led.ledOff();
  this.ledStatus = false;
}

WS2811Module.prototype.turnOff = function turnOff() {
  if (this.blinkInterval) {
    clearInterval(this.blinkInterval);
    this.blinkInterval = false;
    // this.ledOff();
    // return;
  }

  this.ledOff();
};

WS2811Module.prototype.turnOn = function (hexColor) {
  const rgbColor = hexToRGB(hexColor);
  if (this.blinkInterval) {
    clearInterval(this.blinkInterval);
    this.blinkInterval = false;
    // this.ledOn(rgbColor[0], rgbColor[1], rgbColor[2]);
  }

  this.ledOn(rgbColor[0], rgbColor[1], rgbColor[2]);
}

WS2811Module.prototype.turnOnRGB = function (red, green, blue) {
  if (this.blinkInterval) {
    clearInterval(this.blinkInterval);
    this.blinkInterval = false;
    // this.ledOn(red, green, blue);
    // return;
  }

  this.ledOn(red, green, blue);
}

WS2811Module.prototype.blink = function blink(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.ledColor.red = rgbColor[0];
  this.ledColor.green = rgbColor[1];
  this.ledColor.blue = rgbColor[2];
  if (!this.blinkInterval) {
    this.ledOn(rgbColor[0], rgbColor[1], rgbColor[2]);
    this.blinkInterval = setInterval(() => {
      this.toggle();
    }, 333);
  }
}

WS2811Module.prototype.toggle = function toggle() {
  if (this.ledStatus) {
    this.ledOff();
  } else {
    this.ledOn(this.ledColor.red, this.ledColor.green, this.ledColor.blue);
  }
}

WS2811Module.prototype.allLedOn = function allLedOn(red, green, blue) {
  this.led.allLedOn(red, green, blue);
  this.allStatus = true;
}

WS2811Module.prototype.allLedOff = function allLedOff() {
  this.led.allLedOff();
  this.allStatus = false;
}

WS2811Module.prototype.allOff = function allOff() {
  if (this.allBlinkInterval) {
    clearInterval(this.allBlinkInterval);
    this.allBlinkInterval = false;
    // this.allLedOff();
    // return;
  }

  this.allLedOff();
};

WS2811Module.prototype.allOnRGB = function (red, green, blue) {
  if (this.allBlinkInterval) {
    clearInterval(this.allBlinkInterval);
    this.allBlinkInterval = false;
    // this.allLedOn(red, green, blue);
    // return;
  }

  this.allLedOn(red, green, blue);
}

WS2811Module.prototype.allOn = function (hexColor) {
  const rgbColor = hexToRGB(hexColor);
  if (this.allBlinkInterval) {
    clearInterval(this.allBlinkInterval);
    this.allBlinkInterval = false;
  }

  this.allLedOn(rgbColor[0], rgbColor[1], rgbColor[2]);
}

WS2811Module.prototype.allBlink = function allBlink(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.allColor.red = rgbColor[0];
  this.allColor.green = rgbColor[1];
  this.allColor.blue = rgbColor[2];
  if (!this.allBlinkInterval) {
    this.allLedOn(rgbColor[0], rgbColor[1], rgbColor[2]);
    this.allBlinkInterval = setInterval(() => {
      this.allToggle();
    }, 500);
  }
}

WS2811Module.prototype.allToggle = function allToggle() {
  if (this.allStatus) {
    this.allLedOff();
  } else {
    this.allLedOn(this.allColor.red, this.allColor.green, this.allColor.blue);
  }
}

WS2811Module.prototype.release = function release() {
  clearInterval(this.blinkInterval);
  clearInterval(this.allBlinkInterval);
  this.blinkInterval = false;
  this.allBlinkInterval = false;
  this.led.release();
};

module.exports = WS2811Module;
