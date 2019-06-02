#ifndef NAV_H
#define NAV_H
#ifdef __cplusplus
extern "C" {
#endif
#include "movement.h"

void moveTest(float speed);

struct movement_info moveCenter(float speed);

struct movement_info turnCenter(float speed);

struct movement_info turn180Center(float speed);

#ifdef __cplusplus
}
#endif
#endif /* NAV_H */
