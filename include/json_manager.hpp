#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

class JsonManager
{
public:
    JsonManager() = default;
    JsonManager(const std::string &path);
    ~JsonManager() = default;

    nlohmann::json getData();
    void setPathToJson(const std::string &path);
    std::string toString() const;
    std::filesystem::path getPathFromRoot(const std::filesystem::path& path = "");
private:
    std::string m_path_to_json;
    nlohmann::json m_json_data;
    
    /**
     * Parses the json from the current m_path_to_json
     * True for success, else false
     */
    bool parseJson();   
};

JsonManager::JsonManager(const std::string &path):
    m_path_to_json(path)
{
    if (!parseJson())
    {
        std::cout << "[JsonManager] Error! Wrong Json path is given to read! path = " << m_path_to_json << std::endl;
    }
}

void JsonManager::setPathToJson(const std::string &path)
{
    m_path_to_json = path;
    if (!parseJson())
    {
        std::cout << "[JsonManager] Error! Wrong Json path is given to read! path = " << m_path_to_json << std::endl;
    }
}

bool JsonManager::parseJson()
{
    std::ifstream ifs(m_path_to_json);
    if (!ifs.is_open()) {
        m_json_data = nlohmann::json::object();
        return false;
    }
    m_json_data = nlohmann::json::parse(ifs);
    return true;
}

std::string JsonManager::toString() const
{
    return m_json_data.dump();
}

nlohmann::json JsonManager::getData()
{
    return m_json_data;
}

std::filesystem::path JsonManager::getPathFromRoot(const std::filesystem::path& path)
{
    std::filesystem::path path_to_root{std::filesystem::current_path().parent_path()};
    path_to_root += path; 
     return  path_to_root;
}