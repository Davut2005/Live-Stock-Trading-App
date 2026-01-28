#pragma once
#include "../../libs/crow.h"

class AdminRouter {
public:
    static void registerRoutes(crow::SimpleApp& app);
};
