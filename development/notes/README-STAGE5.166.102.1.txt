Stage 5.166.102.1 - Snow Atlas Picker Qt6 Compile Hotfix
29 October 2026

INSTALL
  Overlay this full-source package on 5.166.102 and rebuild CoderGirl.
  Expected splash: Build: 5.166.102.1.291026

FIX
  gamedesigner.cpp, the weatherPickTile clicked handler in world settings:
  [=, &chosenWeatherTile] unintentionally copied the local QDialog, which is
  noncopyable. Qt also treats by-value captures as const within the handler,
  causing conversions from const QWidget* to QWidget* for QMessageBox and
  chooseGameAtlasCell.
  Now captures dialog by reference and names the other required captures.

UNCHANGED
  Generated game runtime, the camera-aware rain/snow, thunder timing/bursts,
  weather serialization, game assets and user-maintained main.c.

VALIDATION
  Source regression, original Stage 5.166.102 weather tests and archive
  checks. Qt6 build cannot be run in this environment. Please confirm your
  desktop build and open the snow tile picker in World Settings.
