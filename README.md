# Card Game README

## Overview
This is a turn-based card game where the goal is to be the first player to empty your deck. You can play cards that match the color or number of the current original card, and use special cards to impact your opponent or change the game dynamics.

## How to Play

### 1. Start Your Turn
- At the beginning of your turn, check the **original card** and your **current hand**.
- You can play a card if:
  - Its **color** matches the original card's color.
  - Its **number** matches the original card's number.

### 2. Playing a Card
- To play a card, type its name exactly as it appears in your hand.
- **Example:**
  Your cards: R6 B4 G2
  Original card: Y2
  - In this case, you can only play **G2**, as its number matches the original card.

### 3. Drawing a Card
- If you cannot play any of your cards, type **`d`** to draw a card from the draw deck.

## Special Cards

In addition to regular cards, there are special cards that allow you to perform unique actions. To play a special card, type the name of the card exactly as it appears.

- **`add`**: Adds two cards to your opponent's deck.
- **`wild`**: Lets you change the original card's color. After playing this card, choose a new color (`R`, `B`, `G`, `Y`).
- **`swap`**: Swaps your entire deck with your opponent's deck.

## How to Win
- The objective is to empty your deck before your opponent.
- If your deck is empty at any point during your turn, you win!

## Example Turn

Scenario:
Your cards: R6 B4 G2 add
Original card: Y2

Your Options:
1. **Play a matching card**:
   - Type **G2** (its number matches the original card).
2. **Play a special card**:
   - Type **add** to add two cards to your opponent's deck.
3. **Draw a card**:
   - Type **`d`** if none of your cards can be played.

## Game Features
- **Dynamic Turns**: Each turn, players can play a matching card, use a special card, or draw a card.
- **Color-coded Display**: Cards are displayed in color (e.g., red for `R`, blue for `B`), making it easy to identify their type.
- **Strategic Gameplay**: Use special cards wisely to disrupt your opponent and gain an advantage.

## Key Commands
Command         | Action
----------------|--------------------------------------------
**Card Name**   | Play the specified card (e.g., `R6`, `add`)
**`d`**         | Draw a card from the draw deck
**`wild`**      | Play a wild card and choose a new color
**`swap`**      | Swap your deck with your opponent's deck

## Tips for Success
1. **Plan Ahead**:
   - Use special cards like **`add`** and **`swap`** strategically to disrupt your opponent.
2. **Wild Cards**:
   - Save wild cards for when you're stuck or need to change the game's flow.
3. **Minimize Your Deck**:
   - Play cards quickly to reduce the size of your deck and increase your chances of winning.

## Troubleshooting
- **Invalid Input**:
  - Ensure you type the card or command exactly as it appears in the game.
- **Empty Draw Deck**:
  - The draw deck will automatically be reshuffled if it runs out of cards.
