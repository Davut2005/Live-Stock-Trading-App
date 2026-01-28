#include "AdminRouter.h"

void AdminRouter::registerRoutes(crow::SimpleApp& app) {

    // GET /api/admin/health
    CROW_ROUTE(app, "/api/admin/health")
    ([](){
        crow::json::wvalue x;
        x["status"] = "OK";
        x["uptime_seconds"] = 120; // Mock uptime
        x["memory_usage_mb"] = 45.2;
        x["active_threads"] = 4;
        return crow::response(x);
    });

    // POST /api/admin/shutdown
    CROW_ROUTE(app, "/api/admin/shutdown").methods(crow::HTTPMethod::Post)
    ([&app](){
        // In a real app we might protect this or fire an async shutdown
        // app.stop(); // This would stop the server
        return crow::response(200, "Shutdown sequence initiated");
    });
    
    // GET /api/admin/logs
    CROW_ROUTE(app, "/api/admin/logs")
    ([](){
        // Return simulated recent logs
        crow::json::wvalue x;
        std::vector<std::string> logs = {
            "[INFO] Server started",
            "[INFO] Market data connected",
            "[WARN] Latency spike detected in feed"
        };
        
        std::vector<crow::json::wvalue> logJson;
        for(const auto& l : logs) logJson.push_back(l);
        
        x["logs"] = std::move(logJson);
        return crow::response(x);
    });
}
