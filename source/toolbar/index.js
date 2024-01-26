const uneditableSearchbar = document.getElementById("uneditable-searchbar");
const uneditableSearchbarText = document.getElementById(
  "uneditable-searchbar-text"
);
const editableSearchbar = document.getElementById("editable-searchbar");

let searchbarUrl = "";

function updateSearchbar(url) {
  searchbarUrl = url.startsWith("https://")
    ? url.substring(8, url.lastIndexOf("/"))
    : url;
  uneditableSearchbarText.innerHTML = searchbarUrl;
  editableSearchbar.value = searchbarUrl;
}

function showEditableSearchbar() {
  uneditableSearchbar.classList.add("hidden");
  editableSearchbar.classList.remove("hidden");
  editableSearchbar.focus();
  editableSearchbar.select();
}

function hideEditableSearchbar() {
  uneditableSearchbar.classList.remove("hidden");
  editableSearchbar.classList.add("hidden");
}

uneditableSearchbar.addEventListener("click", showEditableSearchbar);
editableSearchbar.addEventListener("focusout", hideEditableSearchbar);
editableSearchbar.addEventListener("keydown", (event) => {
  // Check if pressed enter key
  if (event.key === "Enter") {
    updateSearchbar(editableSearchbar.value);
    hideEditableSearchbar();
  }
});

updateSearchbar("https://google.com/");
