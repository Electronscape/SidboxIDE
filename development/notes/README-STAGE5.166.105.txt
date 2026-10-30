CoderGirl IDE Stage 5.166.105 (29 October 2026)
REPEATABLE STOMPABLE ENEMY LOOT
===================================

Separate systems, different rules:

1. "Item dropped when defeated" remains the original one-owner hidden
   Collectable (quest reward) path. Two enemies/breakables still CANNOT
   own the same quest pickup. No changes to its runtime behaviour.

2. "Random loot pool" is NEW for Stompable Enemy objects. Select up to
   eight ordinary Collectable resource templates, set minimum and maximum
   drops to 0..8, and the enemy spawns that many independently collectable
   instances on defeat. Each drop chooses uniformly among the selected
   templates, with duplicates allowed. Examples:
     - Coin [one template], min 1, max 1 => one coin
     - Coin [one template], min 1, max 8 => 1 to 8 coins
     - Coin + Heart + Gem, min 3, max 8 => 3 to 8 mixed items
     - min 0, max 1 => 50% chance to drop one item

Ordinary loot eligibility:
 - The resource must already be a Collectable in the SAME world. It can
   start hidden; its drawing/collision sprite and pickup settings are
   used as a template. No separate duplicate PPB allocation is made.
 - Coin (pickup kind 1), Health (2), Gem (4) are eligible by default.
 - Custom kinds can opt in on their Collectable properties using
   "Allow as repeatable enemy loot (custom kind)".
 - Key kind 3, persistent Collectables, and any item reserved as an
   EXCLUSIVE reward by a Breakable or Enemy are ALWAYS excluded. The
   exporter REJECTS invalid or missing references even if they appear
   in hand-edited .sbgm data.
 - If the template is visible in the world, that original Collectable
   remains independent and visible; hide it if it should only provide
   enemy loot artwork/settings.

Runtime:
 - Uses bounded (8 per loot-bearing enemy, at most 64 WORLD-LOCAL)
   pickup slots, no heap allocation. If all slots are occupied, excess
   drops are omitted until a player collects existing loot.
 - Copies the loaded Collectable's gfxbob descriptor and pickup rules,
   not the whole graphics atlas or source's mutable position.
 - Lightweight scatter, gravity, tilemap collision and deferred pickup
   until landing; uses the existing pickup callback and HUD/inventory.
 - Active loot positions/velocities/template IDs are snapshotted when
   leaving a world and included in TFCard saves for worlds using loot;
   collected drops don't regenerate after returning.
 - No tilemap means ordinary-loot export is rejected, as loot needs
   the tilemap for physical falling/landing.
 - Changes generated world-controller save payloads for worlds where
   loot is enabled; old saves might require a new slot after regenerate.
 - Does NOT modify hand-maintained main.c.

INSTALL / TEST
--------------
Extract over Stage 5.166.104, rebuild IDE, check splash:
  Build: 5.166.105.291026

In Game Designer, place a Coin Collectable (can be Hidden until activated),
open a Stompable Enemy -> Defeat Reward -> Random loot pool, choose Coin,
set minimum 1 and maximum 8, save. "Regenerate ALL Worlds" and rebuild
The Tiny Red Riot. Stomp the enemy repeatedly in new games, count drops,
collect coins, leave and return, save and reload. Test a 2-type pool too.

VALIDATION
----------
- Focused regression tests in development/tests/test_stage5166_105_enemy_loot.py,
  including a compiled native C simulation of 8+1 drops and gravity.
- Earlier ledge, object-type and weather regression tests pass.
- Full Qt6 IDE build and actual SIDBOX 50Hz/TFCard testing not available
  in the source-validation environment; must be verified on target.
