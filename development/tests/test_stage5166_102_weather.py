"""Source and movement regressions for Weather Stage 5.166.102.
Run: python3 development/tests/test_stage5166_102_weather.py
"""
from pathlib import Path
import unittest
ROOT = Path(__file__).resolve().parents[2]

def h(v):
    v &= 0xffffffff
    v ^= v >> 16
    v = (v * 0x7feb352d) & 0xffffffff
    v ^= v >> 15
    v = (v * 0x846ca68b) & 0xffffffff
    return (v ^ (v >> 16)) & 0xffffffff

SEED = h(0x7beab187 ^ (652 * 0x9e3779b9) ^ (240 * 0x85ebca6b))

def particles(camx, camy, tick, size=5, wind=-2, width=480, height=320):
    wind_offset = wind*tick
    first_col = (camx-wind_offset)//width
    result={}
    for rx in range(2):
        cellx=first_col+rx
        for i in range(64):
            motion=h(SEED ^ ((i+1)*0x9e3779b9) ^ (cellx*0x85ebca6b))
            speed=1+((motion>>16)%3)
            travel=tick*speed
            first_row=(camy-travel)//height
            for ry in range(2):
                celly=first_row+ry
                seed=h(motion ^ (celly*0xc2b2ae35))
                worldx=cellx*width+(h(seed^0x6d2b79f5)%width)+wind_offset
                worldy=celly*height+(seed%height)+travel
                x,y=worldx-camx, worldy-camy
                if -size <= x < width and -size <= y < height:
                    result[(cellx,celly,i)]=(x,y,speed)
    return result

class Weather(unittest.TestCase):
    def test_no_lower_edge_wrap(self):
        # Every surviving flake falls downward by exactly its own speed,
        # even when its underlying virtual chunk boundary moves.
        for t in (0,100,200,319,320,640,1200,1800,5000):
            a=particles(100,70,t)
            b=particles(100,70,t+1)
            shared=a.keys() & b.keys()
            self.assertGreater(len(shared),2)
            for key in shared:
                x0,y0,speed=a[key]
                x1,y1,_=b[key]
                self.assertEqual(y1-y0,speed)
                self.assertEqual(x1-x0,-2)
        # A flake that exits the bottom is not re-spawned in the bottom
        # band in the next frame under a new identity.
        for t in (300,450,620,1100,2100):
            a=particles(140,200,t)
            b=particles(140,200,t+1)
            new=b.keys()-a.keys()
            for key in new:
                x,y,speed=b[key]
                self.assertTrue(y <= speed+5 or x<=-3 or x>=470,
                    (t,key,(x,y,speed)))
    def test_camera_motion_preserves_world_positions(self):
        a=particles(1000,200,1457)
        b=particles(1017,210,1457)
        common=a.keys() & b.keys()
        self.assertGreater(len(common),10)
        for key in common:
            self.assertEqual(a[key][0]-b[key][0],17)
            self.assertEqual(a[key][1]-b[key][1],10)
    def test_snapshot_resource_embeds_single_tile(self):
        code=(ROOT/'gameworldsnapshot.h').read_text()
        for required in ('particleAtlasId','particleTileSize','weatherBitmapDeclarations',
                         'sheet.constScanLine','weatherBitmapSymbols.at(i)'):
            self.assertIn(required,code)
    def test_editor_uses_registered_resources_and_shared_selector(self):
        code=(ROOT/'gamedesigner.cpp').read_text()
        self.assertIn('weatherAtlas->addItem(resource.name, resource.id)',code)
        self.assertIn('chooseGameAtlasCell(&dialog, sheet, tile',code)
        self.assertNotIn('Snow atlas tile ID', code)
    def test_lightning_bursts_without_changing_interval_setting(self):
        code=(ROOT/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
        for required in ('weather_burst_remaining','weather_burst_pause',
                         'weather_interval / 2u +','weather_flash_peak = (uint8_t)(25u +',
                         'source_y = camera_y - travel'):
            self.assertIn(required,code)

if __name__=='__main__':unittest.main()
