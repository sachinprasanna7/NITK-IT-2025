document.getElementById('login-form').addEventListener('submit', function(event) {
    event.preventDefault(); // prevent form from submitting normally

    // Get input values
    var username = document.getElementById('username').value;
    var password = document.getElementById('password').value;

    // Check if username and password match expected values
    if (username === 'user' && password === 'abc123') {
      // Redirect to user.html page
      window.location.href = 'user.html';
    } else {
      // Display error message
      document.getElementById('error-message').style.display = 'block';
    }
  });


  
  // Get the modal
  var modal = document.querySelector(".modal");

  // Get the book images with class "enlarge"
  var images = document.querySelectorAll(".enlarge");

  // Loop through the images and add click event listeners
  for (var i = 0; i < images.length; i++) {
    images[i].addEventListener("click", function() {
      // Get the book image source and alt text
      var src = this.getAttribute("src");
      var alt = this.getAttribute("alt");

      // Set the HTML content of the modal to display the selected book
      modal.innerHTML = `
        <div class="modal-content">
          <span class="close">&times;</span>
          <img src="${src}" alt="${alt}" style="width: 80%;">
          <h3>${alt}</h3>
          <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam eget dui ac est rhoncus pretium. Donec commodo ultrices magna eu bibendum. Nunc efficitur ligula id lorem ultricies, vitae hendrerit purus congue. Aenean feugiat, libero at suscipit eleifend, libero tellus imperdiet lectus, sed blandit magna massa eget nunc.</p>
          <button>Add to Cart</button>
          <button>Buy Now</button>
        </div>
      `;

      // Show the modal
      modal.style.display = "block";

      // Get the close button and add a click event listener to hide the modal
      var closeBtn = document.querySelector(".close");
      closeBtn.addEventListener("click", function() {
        modal.style.display = "none";
      });
    });
  }
