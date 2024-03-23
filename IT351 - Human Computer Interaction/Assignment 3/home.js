function redirectToCanvas(letter) {
    // Redirect to canvas.html with the selected letter as a query parameter
    window.location.href = `canvas.html?letter=${letter}`;
}

function redirectToCanvasB(){
    window.location.href = `B.html`;

}

document.addEventListener("DOMContentLoaded", function() {
    const greetingButton = document.getElementById('greetingButton');
    const audio = new Audio('audio/welcome.mp3');

    greetingButton.addEventListener('click', function() {
        audio.play();
    });
});


document.addEventListener("DOMContentLoaded", function() {
    // Retry button event listener
    var retryButtons = document.getElementsByClassName("letterbuttonB");
    for (var i = 0; i < retryButtons.length; i++) {
        retryButtons[i].addEventListener("click", function() {
            window.location.href = "B.html"; // Redirect to canvas.html
        });
    }

});