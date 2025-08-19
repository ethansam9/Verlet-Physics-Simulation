#include "game.h"

int main(void) {
    bool exitStatus = EXIT_FAILURE;

    Game *game = NULL;

    if (GameNew(&game)) {
        GameRun(game);
        exitStatus = EXIT_SUCCESS;
    }

    GameFree(&game);
    return exitStatus;
}
