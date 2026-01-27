// Wait for the entire HTML document to be loaded before running the script
document.addEventListener('DOMContentLoaded', () => {

    // ---CONFIGURATION---
    // Set the correct username and password here.
    const CORRECT_USERNAME = "alexchase";
    const CORRECT_PASSWORD = "ilovecats123";

    // ---ELEMENT SELECTORS---
    // Get references to the HTML elements we need to interact with
    const loginForm = document.getElementById('login-form');
    const loginContainer = document.getElementById('login-container');
    const successContainer = document.getElementById('success-container');

    // ---EVENT LISTENER---
    // Listen for the form to be submitted
    loginForm.addEventListener('submit', (event) => {
        // Prevent the default form submission behavior (which would reload the page)
        event.preventDefault();

        // Get the values entered by the user from the input fields
        const usernameInput = document.getElementById('username').value;
        const passwordInput = document.getElementById('password').value;

        // ---AUTHENTICATION LOGIC---
        // Check if the entered username and password match the correct ones
        if (usernameInput === CORRECT_USERNAME && passwordInput === CORRECT_PASSWORD) {
            // If they match, hide the login form and show the success message
            console.log("Login successful!");
            loginContainer.classList.add('hidden'); // Hide login form
            successContainer.classList.remove('hidden'); // Show success message
        } else {
            // If they don't match, alert the user
            alert("Incorrect username or password. Please try again.");
            // Optional: Clear the form for another attempt
            loginForm.reset();
        }
    });
});