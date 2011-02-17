#ifndef CONSTANTS_H
#define CONSTANTS_H

#define eps 0.0001f

typedef int mytype;

extern const int multiplier;
extern const double maxHorizontalSpeed;
extern const double maxHorizontalRunningSpeed;
extern const double horizontalSpeedStep;
extern const double horizontalRunningSpeedStep;
extern const int screenMinX;
extern const int screenMinY;
extern const int screenMaxX;
extern const int screenMaxY;
extern const int screenSizeX;
extern const int screenSizeY;
extern const int tileSizeX;
extern const int tileSizeY;
extern const int tileSizeXmult;
extern const int tileSizeYmult;
extern const int milisecondsBetweenGameCycles;
extern const int milisecondsBetweenInputCycles;
extern const double maxVerticalSpeed;
extern const double verticalSpeedStep;
extern const int jumpDelay;
extern double friction;
extern double bounce;
extern double drag;
extern double gravity;

#endif // CONSTANTS_H
