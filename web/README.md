# Web Tic Tac Toe

This folder contains a browser version of the Tic Tac Toe game that runs independently from the main C++ codebase.

## Files

- `index.html` — main web page
- `style.css` — UI styling
- `script.js` — game logic and AI implementation

## Run

Open `web/index.html` in a browser.

## Gameplay

- The player is `X`.
- The AI is `O`.
- Enter moves as `row col` (0-indexed) in the input box.
- Press Enter or click Submit to play.
- The AI uses a Minimax algorithm and plays optimally.

## Notes

This version does not modify the existing C++ project files. It is self-contained inside the `web/` folder.

To show the owl image in the page background, save the attached image into `web/owl-bg.jpg`. The design will then blend the feathered dark background with your owl face.
