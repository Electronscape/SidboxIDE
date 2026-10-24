# Stage 5.76 | Operator and ternary continuation indentation

**Normal right-click Format Sourcecode** now indents source lines that continue
at a visible operator one additional real tab beyond the originating statement,
including `?` / `:` ternary branches and arithmetic/logical continuations.
Continuation chains share the same originating indentation (no cumulative
staircase), including when a preceding line closes a multiline function call. Indentation changes only: no code is joined, split or rewritten
by this rule. Parenthesis/bracket continuation handling remains unchanged.

Example:

```c
world_player.width = player_physics.hitbox_w
	? player_physics.hitbox_w : active_player_sprite->width;
world_player.height = player_physics.hitbox_h
	? player_physics.hitbox_h : active_player_sprite->height;
world_player.offset_x = player_physics.hitbox_x;
```

Outside `(...)` and `[...]`, only an explicit leading/trailing operator is
used to infer an expression continuation. Blank lines, comment boundaries,
preprocessor directives and completed statements do not carry the indentation
hint into following code. `case`/`default` and braces retain their treatment.
The separate **Format SourceCode LineBy** command remains unchanged.

Source checks and an independent test model were run here; Qt6 libraries are
unavailable in this environment, so final Fedora compilation and GUI tests
remain necessary. Test with a scratch file before using on large source files.

Modified source files: `codeeditor.cpp`, `splashscreenwidget.cpp`.
