# Stage 5.35 - PNG colour reuse

See `STAGE5.35-REUSE-PNG-PALETTE-COLOURS.md` for details and testing instructions.

PNG importer gains an optional "Reuse matching colours" checkbox in Generate mode. This retains original indices for matching colours already in the project CLUT, adds only genuinely new colours within the selected writable index range, and preserves the prior unchecked behaviour. No game runtime files changed.

Build: 5.35.231026
