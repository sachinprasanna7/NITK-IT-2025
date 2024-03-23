document.addEventListener("DOMContentLoaded", function () {
  // Function to play the intro audio
  function PlayIntroAudio() {
    const audio = new Audio('audio/A.mp3');
    audio.play();
  }

  // Call the function to play the intro audio
  PlayIntroAudio();

  // Your existing code...
  // Paste the rest of your code here
});

// Display the modal
function showModal() {
  var modal = document.getElementById("modal");
  modal.style.display = "block";

  // Close the modal after 5 seconds
  setTimeout(function () {
    modal.style.display = "none";
  }, 3000);
}

// Close the modal when the close button is clicked
document.getElementsByClassName("close")[0].onclick = function () {
  var modal = document.getElementById("modal");
  modal.style.display = "none";
};


// Display the success modal
function openSuccessModal() {
  var modal = document.getElementById("successModal");
  modal.style.display = "block";
}

document.getElementsByClassName("sucess-close")[0].onclick = function () {
  var modal = document.getElementById("successModal");
  modal.style.display = "none";
}



document.addEventListener("DOMContentLoaded", function () {
  // Retry button event listener
  var retryButtons = document.getElementsByClassName("retry-button");
  for (var i = 0; i < retryButtons.length; i++) {
    retryButtons[i].addEventListener("click", function () {
      window.location.href = "canvas.html"; // Redirect to canvas.html
    });
  }

  // Next button event listener
  var nextButtons = document.getElementsByClassName("next-button");
  for (var i = 0; i < nextButtons.length; i++) {
    nextButtons[i].addEventListener("click", function () {
      window.location.href = "B.html"; // Redirect to B.html
    });
  }

  // Home button event listener
  var homeButtons = document.getElementsByClassName("home-button");
  for (var i = 0; i < homeButtons.length; i++) {
    homeButtons[i].addEventListener("click", function () {
      window.location.href = "home.html"; // Redirect to home.html
    });
  }
});




//Button Sound Effects
document.addEventListener("DOMContentLoaded", function () {
  const helpButton = document.getElementById('helpButton');
  const audio = new Audio('audio/instructions.mp3');

  helpButton.addEventListener('click', function () {
    audio.play();
  });

  const buttonclickaudio = new Audio('audio/click1.mp3');

  const backButton = document.getElementById('backButton');
  backButton.addEventListener('click', function () {
    buttonclickaudio.play();
  });

  const clearButton = document.getElementById('clearButton');
  clearButton.addEventListener('click', function () {
    buttonclickaudio.play();
  });

  const nextButton = document.getElementById('nextButton');
  nextButton.addEventListener('click', function () {
    buttonclickaudio.play();
  });
});



function PlayFireworks() {
  "use strict";

  let canvas, width, height, ctx;
  let fireworks = [];
  let particles = [];

  function setup() {
    canvas = document.getElementById("fireworksCanvas");
    setSize(canvas);
    ctx = canvas.getContext("2d");
    // ctx.fillStyle = "#000000";
    // ctx.fillRect(0, 0, width, height);
    fireworks.push(new Firework(Math.random() * (width - 200) + 100));
    window.addEventListener("resize", windowResized);
    document.addEventListener("click", onClick);
  }

  setTimeout(setup, 1);

  function loop() {

    ctx.globalAlpha = 0.1;
    ctx.globalAlpha = 1;

    for (let i = 0; i < fireworks.length; i++) {
      let done = fireworks[i].update();
      fireworks[i].draw();
      if (done) fireworks.splice(i, 1);
    }

    for (let i = 0; i < particles.length; i++) {
      particles[i].update();
      particles[i].draw();
      if (particles[i].lifetime > 80) particles.splice(i, 1);
    }

    if (Math.random() < 1 / 60) fireworks.push(new Firework(Math.random() * (width - 200) + 100));
  }
  setInterval(loop, 1 / 60);
  //setInterval(loop, 100/60);
  class Particle {
    constructor(x, y, col) {
      this.x = x;
      this.y = y;
      this.col = col;
      this.vel = randomVec(2);
      this.lifetime = 0;
    }

    update() {
      this.x += this.vel.x;
      this.y += this.vel.y;
      this.vel.y += 0.02;
      this.vel.x *= 0.99;
      this.vel.y *= 0.99;
      this.lifetime++;
    }

    draw() {
      ctx.globalAlpha = Math.max(1 - this.lifetime / 80, 0);
      ctx.fillStyle = this.col;
      ctx.fillRect(this.x, this.y, 2, 2);
    }
  }

  class Firework {
    constructor(x) {
      this.x = x;
      this.y = height;
      this.isBlown = false;
      this.col = randomCol();
    }

    update() {
      this.y -= 3;
      if (this.y < 350 - Math.sqrt(Math.random() * 500) * 40) {
        this.isBlown = true;
        for (let i = 0; i < 60; i++) {
          particles.push(new Particle(this.x, this.y, this.col))
        }
      }
      return this.isBlown;
    }

    draw() {
      ctx.globalAlpha = 1;
      ctx.fillStyle = this.col;
      ctx.fillRect(this.x, this.y, 2, 2);
    }
  }

  function randomCol() {
    var letter = '0123456789ABCDEF';
    var nums = [];

    for (var i = 0; i < 3; i++) {
      nums[i] = Math.floor(Math.random() * 256);
    }

    let brightest = 0;
    for (var i = 0; i < 3; i++) {
      if (brightest < nums[i]) brightest = nums[i];
    }

    brightest /= 255;
    for (var i = 0; i < 3; i++) {
      nums[i] /= brightest;
    }

    let color = "#";
    for (var i = 0; i < 3; i++) {
      color += letter[Math.floor(nums[i] / 16)];
      color += letter[Math.floor(nums[i] % 16)];
    }
    return color;
  }

  function randomVec(max) {
    let dir = Math.random() * Math.PI * 2;
    let spd = Math.random() * max;
    return { x: Math.cos(dir) * spd, y: Math.sin(dir) * spd };
  }

  function setSize(canv) {
    canv.style.width = (innerWidth) + "px";
    canv.style.height = (innerHeight) + "px";
    width = innerWidth;
    height = innerHeight;

    canv.width = innerWidth * window.devicePixelRatio;
    canv.height = innerHeight * window.devicePixelRatio;
    canvas.getContext("2d").scale(window.devicePixelRatio, window.devicePixelRatio);
  }

  function onClick(e) {
    fireworks.push(new Firework(e.clientX));
  }

  function windowResized() {
    setSize(canvas);
    // ctx.fillStyle = "#000000";
    // ctx.fillRect(0, 0, width, height);
  }
}



// Code for Drawing on Canvas
document.addEventListener("DOMContentLoaded", function () {
  const canvas = document.getElementById('drawingCanvas');
  const context = canvas.getContext('2d');

  const dotRadius = 25; // Radius of the allowed drawing area around each dot
  let isDrawing = false;
  let isCorrect = false;
  let timesLifted = 0;

  let dotCoordinates = [
    [65, 220],   // lower left dot
    [150, 50],   // upper middle dot
    [235, 220]   // lower right dot
  ];

  for (let i = 0; i < 80; i = i + 10) {
    //it should be on the line connecting the lower left dot and the upper middle dot
    let x = 65 + i;
    let y = 350 - 2 * x;

    dotCoordinates.push([x, y]);
  }

  for (let i = 0; i < 80; i = i + 10) {
    //it should be on the line connecting the lower right dot and the upper middle dot
    let x = 235 - i;
    let y = 2 * x - 250;

    dotCoordinates.push([x, y]);
  }

  for (let i = 0; i < 80; i = i + 10) {
    //it should be on the line connecting the lower left dot and the lower right dot
    let x = 115 + i;
    let y = 145;

    dotCoordinates.push([x, y]);
  }

  let touchedDots = []
  for (let i = 0; i < dotCoordinates.length; i++) {
    touchedDots.push(false);
  }

  let drawnCoordinates = []

  function checkIntersections(dotCoordinates, drawnCoordinates) {
    //loop through the drawn coordinates
    for (let i = 0; i < drawnCoordinates.length; i++) {
      let x = drawnCoordinates[i][0];
      let y = drawnCoordinates[i][1];

      //loop through the dot coordinates

      let atleastOneDotTouched = false;

      for (let j = 0; j < dotCoordinates.length; j++) {
        let dotX = dotCoordinates[j][0];
        let dotY = dotCoordinates[j][1];

        //check if the drawn coordinate is within the radius of the dot
        if (Math.sqrt((x - dotX) ** 2 + (y - dotY) ** 2) <= dotRadius) {
          atleastOneDotTouched = true;
          touchedDots[j] = true;
        }
      }

      if (atleastOneDotTouched == false) {
        return false;
      }
    }

    return true;
  }

  function checkCompletion(touchedDots) {
    isCorrect = touchedDots.every((dot) => dot === true);
    return isCorrect;
  }


  canvas.addEventListener('mousedown', function (event) {
    isDrawing = true;
    const x = event.clientX - canvas.getBoundingClientRect().left;
    const y = event.clientY - canvas.getBoundingClientRect().top;
    context.beginPath();
    context.moveTo(x, y);

    drawnCoordinates.push([x, y]); // Add starting point to coordinates array

  });

  canvas.addEventListener('mousemove', function (event) {
    if (isDrawing) {
      const x = event.clientX - canvas.getBoundingClientRect().left;
      const y = event.clientY - canvas.getBoundingClientRect().top;
      context.lineTo(x, y);
      context.stroke();

      drawnCoordinates.push([x, y]);
    }
  });

  canvas.addEventListener('mouseup', function () {
    timesLifted++;

    if(timesLifted > 1){
      isDrawing = false;
      isCorrect = checkIntersections(dotCoordinates, drawnCoordinates);

      if (isCorrect)
        isCorrect = checkCompletion(touchedDots);

      if (isCorrect) {
        openSuccessModal();
        const audio1 = new Audio('audio/kids_cheering.mp3');
        const audio = new Audio('audio/congratulations.mp3');

        audio1.play();
        audio.play();
      } 

    else {

      //pick a random number between
      showModal();

      //pick a ranom number between 1 and 3
      let randomNumber = Math.floor(Math.random() * 3) + 1;

      //play the wrong audio
      const audio1 = new Audio('audio/wronganswer.mp3');
      const audio = new Audio('audio/tryagain' + randomNumber + '.mp3');
      audio1.play();
      //pause for 2 seconds then play the next audio

      audio.play();

      //clear the canvas
      context.clearRect(0, 0, canvas.width, canvas.height);
      drawAlphabet('A'); // Redraw alphabet dots after clearing

      //reset the touched dots
      for (let i = 0; i < touchedDots.length; i++) {
        touchedDots[i] = false;
      }

      //reset the drawn coordinates
      drawnCoordinates = []
    }

    timesLifted = 0;
  }
  });

  canvas.addEventListener('mouseleave', function () {
    isDrawing = false;
  });

  const clearButton = document.getElementById('clearButton');
  clearButton.addEventListener('click', function () {
    timesLifted = 0;
    context.clearRect(0, 0, canvas.width, canvas.height);
    drawAlphabet('A'); // Redraw alphabet dots after clearing
  });

  function drawAlphabet(letter) {
    context.clearRect(0, 0, canvas.width, canvas.height);

    // Draw dots for the letter 'A'
    if (letter === 'A') {
      context.beginPath();
      drawDot(65, 220);   // lower left dot
      drawDot(150, 50);   // upper middle dot
      drawDot(235, 220);  // lower right dot

      for (let i = 0; i < 80; i = i + 10) {
        //it should be on the line connecting the lower left dot and the upper middle dot
        let x = 65 + i;
        let y = 350 - 2 * x;
        drawDot(x, y);
      }

      for (let i = 0; i < 80; i = i + 10) {
        //it should be on the line connecting the lower right dot and the upper middle dot
        let x = 235 - i;
        let y = 2 * x - 250;
        drawDot(x, y);
      }

      for (let i = 0; i < 80; i = i + 10) {
        //it should be on the line connecting the lower left dot and the lower right dot
        let x = 115 + i;
        let y = 145;

        drawDot(x, y);
      }
    }

    // Add more conditions for other letters
  }

  function drawDot(x, y) {
    context.moveTo(x, y);
    context.arc(x, y, 2, 0, Math.PI * 2);
    context.fillStyle = "black";
    context.fill();
  }

  drawAlphabet('A'); // Initial drawing of alphabet dots
});




//Code for Back Button
document.addEventListener("DOMContentLoaded", function () {
  const backButton = document.getElementById('backButton');
  const buttonclickaudio = new Audio('audio/click1.mp3');
  backButton.addEventListener('click', function () {

    buttonclickaudio.play();
    window.location.href = 'home.html'; // Redirect to the home page
  });

  const nextButton = document.getElementById('nextButton');
  nextButton.addEventListener('click', function () {

    buttonclickaudio.play();
    window.location.href = 'B.html'; // Redirect to the next page
  });
});




//Code for Playing Audio on Hover
document.addEventListener("DOMContentLoaded", function () {
  const planeImage = document.getElementById('aeroplaneimg');
  const audio = document.getElementById('aeroplaneaudio'); // Get the audio element by its ID

  planeImage.addEventListener('mouseover', function () {
    planeImage.style.transition = 'transform 0.5s ease';
    planeImage.style.transform = 'scale(1.1)'; // Increase the scale on hover
    audio.play(); // Play the audio when mouse is over the image
  });

  planeImage.addEventListener('mouseout', function () {
    planeImage.style.transform = 'scale(1)'; // Reset the scale on mouseout
    audio.pause(); // Pause the audio when mouse leaves the image
    audio.currentTime = 0; // Reset audio to the beginning
  });
});
