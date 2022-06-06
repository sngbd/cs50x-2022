var button = document.getElementById("btn");
window.onscroll = function() {scrollFunction()};
function scrollFunction() {
  if (document.body.scrollTop > 1000) {
    button.style.display = "block";
  } else {
    button.style.display = "none";
  }
}
function topFunction() {
  document.body.scrollTop = 0;
}

