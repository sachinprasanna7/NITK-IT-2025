// Display the modal
function showModal() {
	var modal = document.getElementById("modal");
	modal.style.display = "block";
  
	// Close the modal after 3 seconds
	setTimeout(function() {
	  modal.style.display = "none";
	}, 3000);
  }
  
  // Close the modal when the close button is clicked
  document.getElementsByClassName("close")[0].onclick = function() {
	var modal = document.getElementById("modal");
	modal.style.display = "none";
  };


// Display the success modal
function openSuccessModal() {
	var modal = document.getElementById("successModal");
	modal.style.display = "block";
}

document.getElementsByClassName("sucess-close")[0].onclick = function() {
	var modal = document.getElementById("successModal");
	modal.style.display = "none";
}


// Redirection buttons
document.addEventListener("DOMContentLoaded", function() {
    // Retry button event listener
    var retryButtons = document.getElementsByClassName("retry-button");
    for (var i = 0; i < retryButtons.length; i++) {
        retryButtons[i].addEventListener("click", function() {
            window.location.href = "canvas.html"; // Redirect to canvas.html
        });
    }

    // Next button event listener
    var nextButtons = document.getElementsByClassName("next-button");
    for (var i = 0; i < nextButtons.length; i++) {
        nextButtons[i].addEventListener("click", function() {
            window.location.href = "B.html"; // Redirect to B.html
        });
    }

    // Home button event listener
    var homeButtons = document.getElementsByClassName("home-button");
    for (var i = 0; i < homeButtons.length; i++) {
        homeButtons[i].addEventListener("click", function() {
            window.location.href = "home.html"; // Redirect to home.html
        });
    }
});



//Code for Playing Audio for buttons
document.addEventListener("DOMContentLoaded", function() {
    const helpButton = document.getElementById('helpButton');
    const audio = new Audio('audio/instructionsB.mp3');

    helpButton.addEventListener('click', function() {
        audio.play();
    });

	const buttonclickaudio = new Audio('audio/click1.mp3');

	const backButton = document.getElementById('backButton');
	backButton.addEventListener('click', function() {
		buttonclickaudio.play();
	});

	const clearButton = document.getElementById('clearButton');
	clearButton.addEventListener('click', function() {
		buttonclickaudio.play();
	});

	const nextButton = document.getElementById('nextButton');
	nextButton.addEventListener('click', function() {
		buttonclickaudio.play();
	});
});



// Code for Drawing on Canvas
document.addEventListener("DOMContentLoaded", function() {
    const canvas = document.getElementById('drawingCanvas');
    const context = canvas.getContext('2d');

    const dotRadius = 25; // Radius of the allowed drawing area around each dot
    let isDrawing = false;
    let isCorrect = false;

	let dotCoordinates = [
		[203, 220],   // lower right dot
		[203, 180],
		[203, 113],
		[203, 80],
		[65, 250],   // lower left dot
		[65, 150],   // middle left dot
		[65, 50],   // upper left dot
	];

	for (let i = 0; i < 200; i = i + 10) {
		let x = 65;
		let y = 250 - i;
		dotCoordinates.push([x, y]);
	}

	// lower line of B
	for (let i = 0; i < 100; i = i + 10) {
		let x = 65 + i;
		let y = 250;
		dotCoordinates.push([x, y]);
	}

	// upper line of B
	for (let i = 0; i < 100; i = i + 10) {
		let x = 65 + i;
		let y = 50;
		dotCoordinates.push([x, y]);
	}

	// middle line of B
	for (let i = 0; i < 100; i = i + 10) {
		let x = 65 + i;
		let y = 150;
		dotCoordinates.push([x, y]);
	}

	// Upper curve of B
	for (let i = 0; i < 150; i = i + 10) {
		let x = 155 + i;
		let y = 100 - Math.sqrt(50 * 50 - i * i);
		dotCoordinates.push([x, y]);
	}

	// Lower curve of B
	for (let i = 0; i < 150; i = i + 10) {
		let x = 155 + i;
		let y = 200 + Math.sqrt(50 * 50 - i * i);
		dotCoordinates.push([x, y]);
	}

	// Lower curve of B from middle
	for (let i = 0; i < 150; i = i + 10) {
		let x = 155 + i;
		let y = 100 + Math.sqrt(50 * 50 - i * i);
		dotCoordinates.push([x, y]);
	}

	// Upper curve of B from middle
	for (let i = 0; i < 150; i = i + 10) {
		let x = 155 + i;
		let y = 200 - Math.sqrt(50 * 50 - i * i);
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

  
    canvas.addEventListener('mousedown', function(event) {
      isDrawing = true;
      const x = event.clientX - canvas.getBoundingClientRect().left;
      const y = event.clientY - canvas.getBoundingClientRect().top;
      context.beginPath();
      context.moveTo(x, y);

	  drawnCoordinates.push([ x, y ]); // Add starting point to coordinates array

    });
  
    canvas.addEventListener('mousemove', function(event) {
      if (isDrawing) {
        const x = event.clientX - canvas.getBoundingClientRect().left;
        const y = event.clientY - canvas.getBoundingClientRect().top;
        context.lineTo(x, y);
        context.stroke();

		drawnCoordinates.push([x, y]);
      }
    });
  
    canvas.addEventListener('mouseup', function() {
		isDrawing = false;
		isCorrect = checkIntersections(dotCoordinates, drawnCoordinates);

		if(isCorrect)
			isCorrect = checkCompletion(touchedDots);

        if (isCorrect) {
			openSuccessModal();
			const audio1 = new Audio('audio/kids_cheering.mp3');
			const audio = new Audio('audio/congratulations.mp3');

			audio1.play();
        	audio.play();
			
			//PlayFireworks();

        } else {

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
			drawAlphabet('B'); // Redraw alphabet dots after clearing

			//reset the touched dots
			for (let i = 0; i < touchedDots.length; i++) {
				touchedDots[i] = false;
			}

			//reset the drawn coordinates
			drawnCoordinates = []
        }
    });
  
    canvas.addEventListener('mouseleave', function() {
      isDrawing = false;
    });
  
    const clearButton = document.getElementById('clearButton');
    clearButton.addEventListener('click', function() {
      context.clearRect(0, 0, canvas.width, canvas.height);
      drawAlphabet('B'); // Redraw alphabet dots after clearing
    });
  
    function drawAlphabet(letter) {
      context.clearRect(0, 0, canvas.width, canvas.height);
  
      // Draw dots for the letter 'B'
      if (letter === 'B') {
        context.beginPath();
        drawDot(65, 250);   // lower left dot

		// standing line of B
		for (let i = 0; i < 200; i = i + 10) {
			let x = 65;
			let y = 250 - i;
			drawDot(x, y);
		}

		// lower line of B
		for (let i = 0; i < 100; i = i + 10) {
			let x = 65 + i;
			let y = 250;
			drawDot(x, y);
		}

		// upper line of B
		for (let i = 0; i < 100; i = i + 10) {
			let x = 65 + i;
			let y = 50;
			drawDot(x, y);
		}

		// middle line of B
		for (let i = 0; i < 100; i = i + 10) {
			let x = 65 + i;
			let y = 150;
			drawDot(x, y);
		}

		// Upper curve of B
        for (let i = 0; i < 150; i = i + 10) {
            let x = 155 + i;
            let y = 100 - Math.sqrt(50 * 50 - i * i);
            drawDot(x, y);
        }

        // Lower curve of B
        for (let i = 0; i < 150; i = i + 10) {
            let x = 155 + i;
            let y = 200 + Math.sqrt(50 * 50 - i * i);
            drawDot(x, y);
        }

		// Lower curve of B from middle
        for (let i = 0; i < 150; i = i + 10) {
            let x = 155 + i;
            let y = 100 + Math.sqrt(50 * 50 - i * i);
            drawDot(x, y);
        }

		// Upper curve of B from middle
        for (let i = 0; i < 150; i = i + 10) {
            let x = 155 + i;
            let y = 200 - Math.sqrt(50 * 50 - i * i);
            drawDot(x, y);
        }

		// final dots
		drawDot(203, 220);   // lower right dot
		drawDot(203, 180);
		drawDot(203, 113);
		drawDot(203, 80);

      }

      // Add more conditions for other letters
    }
  
    function drawDot(x, y) {
      context.moveTo(x, y);
      context.arc(x, y, 2, 0, Math.PI * 2);
      context.fillStyle = "black";
      context.fill();
    }
  
    drawAlphabet('B'); // Initial drawing of alphabet dots
  });




//Code for Back Button
document.addEventListener("DOMContentLoaded", function() {
    const backButton = document.getElementById('backButton');
	const buttonclickaudio = new Audio('audio/click1.mp3');
    backButton.addEventListener('click', function() {

		buttonclickaudio.play();
        window.location.href = 'home.html'; // Redirect to the home page
    });

	const nextButton = document.getElementById('nextButton');
	nextButton.addEventListener('click', function() {

		buttonclickaudio.play();
		window.location.href = 'B.html'; // Redirect to the next page
	});
});




//Code for Playing Audio on Hover
document.addEventListener("DOMContentLoaded", function() {
    const planeImage = document.getElementById('aeroplaneimg');
    const audio = document.getElementById('aeroplaneaudio'); // Get the audio element by its ID

    planeImage.addEventListener('mouseover', function() {
        planeImage.style.transition = 'transform 0.5s ease';
        planeImage.style.transform = 'scale(1.1)'; // Increase the scale on hover
        audio.play(); // Play the audio when mouse is over the image
    });

    planeImage.addEventListener('mouseout', function() {
        planeImage.style.transform = 'scale(1)'; // Reset the scale on mouseout
        audio.pause(); // Pause the audio when mouse leaves the image
        audio.currentTime = 0; // Reset audio to the beginning
    });
});
  