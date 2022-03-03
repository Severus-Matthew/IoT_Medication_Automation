// Initialize Firebase 
var config = {
    apiKey: "AIzaSyCpr964V-n-y0PDZgfurtDPzuwZc040LJ8",
    authDomain: "experiment-1-98c23.firebaseapp.com",
    databaseURL: "https://experiment-1-98c23.firebaseio.com",
    projectId: "experiment - 1 - 98c23",
    storageBucket: "experiment-1-98c23.appspot.com",
    messagingSenderId: "358789021543",
    appId: "1:358789021543:web:abc7e4a90e9628278d79c2"


};
firebase.initializeApp(config);

// Reference messages collection
var messagesRef = firebase.database().ref();

// Listen for form submit
document.getElementById('contactForm').addEventListener('submit', submitForm);

// Submit form
function submitForm(e){
  e.preventDefault();

  // Get values
  var Hou = getInputVal('Hour');
    var Mi = getInputVal('Min');
    var Hour = parseInt(Hou);
    var Min = parseInt(Mi);
    var email = getInputVal('email');
    var Name = getInputVal('name');

 

  // Save message
  saveMessage(Hour, Min, email, Name);

  // Show alert
  document.querySelector('.alert').style.display = 'block';

  // Hide alert after 3 seconds
  setTimeout(function(){
    document.querySelector('.alert').style.display = 'none';
  },3000);

  // Clear form
  document.getElementById('contactForm').reset();
}

// Function to get get form values
function getInputVal(id){
  return document.getElementById(id).value;
}

// Save message to firebase
function saveMessage(Hour,Min, email, Name){
  var newMessageRef = messagesRef.push();
  messagesRef.update({
      Hour: Hour,
      Min: Min,
      email: email,
      Name :Name
  });
}