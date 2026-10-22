# CoderGirl Stage 5.33: Inventory close, blinking action brackets, box-height trim
22 October 2026. Based on Stage 5.32. IDE and game-helper template changes only; user-owned main.c is untouched.

## Runtime behaviour
- **USE**: a successful stat callback now closes the inventory immediately. Failed USE retains the inventory and does not consume the item.
- **DROP**: when a world drop slot is available and one item is successfully dropped, the inventory closes. Failure (full drop slots, missing item, protected item) retains the inventory. Dropped items remain recoverable, including across world visits in RAM.
- **DESTROY**: the confirmation is still required, defaulting to **NO**. Confirming YES and successfully removing one item closes the inventory. NO, FIRE2/BACK, or unsuccessful deletion returns to the inventory.
- **Brackets**: selection brackets around USE, DROP, DESTROY and NO/YES are visible for 10 game frames and invisible for 10 frames, repeating. The labels never move or blink, and bracket timing resets on selection changes. The source counts `frames` passed to `game_adventure_input`, rather than assuming every draw is one frame. No additional timers or allocations.
- When the confirmation is open, brackets highlight only NO or YES, not the underlying inventory action.

## Box-height changes
- The inventory box and DESTROY confirmation box are 8 pixels shorter. Inventory rows and decorative-border-aware 8px inset are preserved; the footer moves up to reclaim the spare gap.
- NPC dialogue boxes reclaim 8 pixels of unused vertical spacing rather than deleting protective text padding. The gap *before choices* is 1px rather than 9px; when there are no choices, the body starts 16px after the speaker instead of 24px. The configured minimum height also trims by 8px, but automatic expansion still keeps text and choices visible.
- The Adventure Editor dialogue-position preview now uses the same height and gap calculations as the generated runtime. Player reply bubbles are unchanged because their height already exactly fits their lines and padding.

## Installation
1. Back up Stage 5.32. Copy the changed files into the same relative paths in your IDE source tree.
2. Rebuild the IDE. Splash build should show **5.33.221026**.
3. Open your game project, choose **Update Game Project** to regenerate the Adventure helper, then compile the game. **Do not replace the custom game main.c.**
4. On SIDBOX, verify USE closes the bag only after success, DROP closes after dropping, DESTROY YES closes but NO returns to the bag, and brackets toggle every 10 frames. Verify the shorter inventory and dialogue boxes have no border or text clipping.

## Host tests (passed)
- `test_stage533_inventory_polish.py`: generated C strict GCC -std=c11 -Wall -Wextra -Werror, successful/failed USE, DROP, DESTROY YES/NO, blinking bracket coordinates, height trim and NPC text/choice clipping.
- `test_stage532_frame_padding.py`, `test_stage532_inventory_use.py`, `test_stage531_inventory_runtime.py`, `test_stage530_inventory_art_discard.py`, `test_stage528_fire2_fallback.py`, `test_stage527_adventure_secret_choices.py`: passed with updated expectations for the requested inventory-close and height changes.
- Qt6 IDE build was not possible in this environment (Qt6 development headers are unavailable). Physical SIDBOX hardware test remains for the user.
