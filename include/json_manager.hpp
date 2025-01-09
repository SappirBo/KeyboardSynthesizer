#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

class JsonManager
{
private:
    std::string m_path_to_json;
    nlohmann::json m_json_data;
    
    /**
     * Parses the json from the current m_path_to_json
     * True for success, else false
     */
    bool parseJson();
public:
    JsonManager(const std::string &path);
    ~JsonManager();

    template <typename... Keys>
    std::string toString(Keys... keys) const;
};

JsonManager::JsonManager(const std::string &path):
    m_path_to_json(path)
{
    if (parseJson() == false)
    {
        std::cout << "[JsonManager] Error! Wrong Json path is given to read! path = " << m_path_to_json << std::endl;
    }
}

bool JsonManager::parseJson()
{
    std::ifstream ifs(m_path_to_json);
    if (!ifs.is_open()) {
        return false;
    }
    m_json_data = nlohmann::json::parse(ifs);
    return true;
}

JsonManager::~JsonManager()
{
}

template <typename... Keys>
std::string JsonManager::toString(Keys... keys) const
{
    if constexpr (sizeof...(keys) == 0)
    {
        return m_json_data.dump();
    }
    else
    {
        nlohmann::json temp = m_json_data;
        ((temp = temp[keys]), ...);
        return temp.dump();
    }
}