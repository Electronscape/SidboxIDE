#!/usr/bin/env python3
"""Strict nested-rule render smoke test for named events with/without audio and pickups."""
from pathlib import Path
from itertools import product
import re,unittest
ROOT=Path(__file__).resolve().parents[2]
SRC=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
ALL=set(re.findall(r'@IDE_IF\{([A-Z][A-Z_0-9]+)\}',SRC))

def render(text,flags):
 stack=[];active=True;lines=[]
 for line,i in zip(text.splitlines(),range(1,99999)):
  if m:=re.fullmatch(r'\s*@IDE_IF\{([A-Z][A-Z_0-9]+)\}\s*',line):
   stack.append((active,flags.get(m.group(1),False)));active=active and flags.get(m.group(1),False)
  elif line.strip()=='@IDE_ELSE':
   assert stack,(i,line);active=stack[-1][0] and not stack[-1][1]
  elif line.strip()=='@IDE_END':
   assert stack,(i,line);active=stack.pop()[0]
  else:
   assert '@IDE_IF{' not in line,(i,line)
   if active:lines.append(line)
 assert not stack,'unclosed conditional blocks'
 return '\n'.join(lines)

class RuleSmoke(unittest.TestCase):
 def test_combinations(self):
  for audio,pickup,graph in product([False,True],repeat=3):
   flags={s:False for s in ALL}
   flags.update(HAS_ITEMS=True,HAS_WORLDS=True,HAS_AUDIO_WORLDS=audio,HAS_PICKUPS=pickup,
     HAS_NAMED_EVENTS=True,HAS_NAMED_PICKUP_EVENTS=pickup,
     HAS_NAMED_EVENT_LOGIC=graph,HAS_NAMED_PICKUP_LOGIC=graph and pickup,
     HAS_ENEMY_STATE_LOGIC=graph,HAS_TRIGGERS=True,SAVE_PICKUP_ACTIVE=pickup)
   output=render(SRC,flags)
   self.assertIn('static uint8_t cg_named_event_sources',output)
   self.assertIn('void gameworlditems_checkpoint_saved(void)',output)
   self.assertEqual('static uint8_t cg_named_pickup_sources' in output,pickup)
   self.assertEqual('if(cg_named_logic_fired)cg_run_trigger_actions();' in output,graph)
   self.assertEqual('if(cg_named_pickup_logic)cg_run_trigger_actions();' in output,graph and pickup)
   self.assertEqual('if(cg_defeat_logic_event)' in output,graph)
   # No source token nested in a conditional remains unresolved as a directive.
   self.assertNotIn('@IDE_IF{',output)
   self.assertNotIn('@IDE_ELSE',output)
   self.assertNotIn('@IDE_END',output)

if __name__=='__main__':unittest.main()
