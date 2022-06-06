# PasteBox
#### Video Demo: https://www.youtube.com/watch?v=B47y4soXuqA
#### Description:
PasteBox is a Chrome extension whose purpose is to serve as a temporary text clipboard. This extension allows the user to store the clipboard by copy-pasting the desired text to the provided input box or by typing the text manually. It can be useful if the user wants to store some text from the browser but can't be bothered to open up a new file on an external software (notes, for instance) <br>

Once the user clicks the "Paste" button, the input is going to be stored immediately in the localStorage. If the user exit out of extension, that is, via clicking somewhere else on the screen or clicking the extension, once accesses again, it won't show the user's PasteBox clipboard, the user have to click on the "Show" button to show the PasteBox clipboard. "Clear" button serves as a way to clear all of the user's input, that is, the whole PasteBox clipboard. It will clear the localStorage of the extension. Afterwards, the user have to exit the extension to paste a new text.<br>

This project contains a folder named "images" for extension's icons; manifest.json for information or metadata that defines the extension; index.html for user interface with bootstrap styling; and script.js to provides logic to the whole process. The icons are of 16 x 16 px, 48 x 48 px, and 128 x 128 px size, typical of manifest.json required icons. I use manifest version 2 to support browser_action to link index.html and the icon as user interface to the extension. Permission required for manifest.json is storage, for storing text on the localStorage. In index.html I use input tag with type=text for the user to input the text, and three buttons for distinct function that could interact with the user using javascript that I linked at the bottom of the body. Div tag with the id=div after the buttons serves as a place for the clipboard to show. In script.js I first initialize the required variables for doing logic with, then I use chrome.storage.local.get as a way to fetch data from localStorage of the Chrome extension to get the value of the key to access the clipboard. Afterwards are document.querySelector functions to listen to each event happened for each buttons that is in this case is the click event. Lastly are the functions for each button: set() for pasting user input on the PasteBox clipboard, show() for showing the PasteBox clipboard, clear() for clearing the whole clipboard. <br>

Overall, this Chrome extension has a whole lot of room for improvement. The improvements I could think of are as listed:
1. Fetching and pasting he user's clipboard as an option as opposed to manually copy-pasting (provides it as an option, too) it to the input box.
2. Selecting text for deletion as opposed to clearing the whole clipboard.
3. Reducing other inefficiencies such as manually showing the clipboard and exiting the extension before pasting a new text after clearing.