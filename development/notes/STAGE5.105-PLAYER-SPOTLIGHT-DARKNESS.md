# Stage 5.105.251025: Player spotlight darkness

Adds an optional per-world pseudo-lighting effect in **Player Start — World Entry Point**.

- Enable local darkness with player spotlight
- Spotlight radius (clear circle around player)
- Spotlight feather (soft dither edge)

The generated runtime draws the darkness overlay above the playfield but below HUD and dialogue, so menus and dialogue remain readable.

This is a pseudo effect only. It does not recolour tile palettes or provide true per-pixel lighting; it masks the scene using a black overlay with a circular aperture that follows the player.
