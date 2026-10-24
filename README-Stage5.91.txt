CoderGirl Stage 5.91.241026  |  V1 game engine proximity USE interactions

Changes are GENERAL SDK/IDE features (not hardcoded for any game).

Install the DROP-IN by extracting into your existing CoderGirl IDE source
root, preserving file paths, then rebuild the IDE. Keep a backup.

To use: define an Adventure Inventory item, create a Trigger game object,
select the required item and proximity reach in its properties, link its
activation to another object (e.g. disable an active door), save the world,
Update Game Project, rebuild and test on SIDBOX.

Do not overwrite or edit your game main.c. The updated runtime is generated
from the IDE SDK template by Update Game Project.

See STAGE5.91-ITEM-TARGETED-INTERACTIONS.md for full behaviour and limits.
