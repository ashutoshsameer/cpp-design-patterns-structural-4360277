#include <iostream>
#include <string>

using namespace std;

class WorldWeatherAPI
{
public:
    tuple<float, float, string> getWeather(string location)
    {
        cout << "Calling worldWeather with location: " << location << endl;
        float temperature = 20.0f;
        float windSpeed = 5.5f;
        string shortDescription = "Sunny";
        return make_tuple(temperature, windSpeed, shortDescription);
    }
};

class FreeWeather
{
public:
    tuple<float, string> retrieve_weather(string location)
    {
        cout << "Calling freeWeather with location: " << location << endl;
        float temperature = 22.0f;
        string shortDescription = "Sunny";
        return make_tuple(temperature, shortDescription);
    }
};

class RealtimeWeatherService
{
public:
    tuple<float, float, string> weatherConditions(string location)
    {
        cout << "Calling realtimeWeather with location: " << location << endl;
        float temperature = 19.5f;
        float humidity = 60.0f;
        string shortDescription = "Partly cloudy with a chance of rain";
        return make_tuple(temperature, humidity, shortDescription);
    }
};

class WeatherFacade
{
public:
    WeatherFacade()
    : m_wwapi()
    , m_free()
    , m_rtw()
    {}

    tuple<float, float, string> currentWeather(const string& location)
    {
        tuple<float, float, string> wwapi = m_wwapi.getWeather(location);
        tuple<float, string> free = m_free.retrieve_weather(location);
        tuple<float, float, string> rtw = m_rtw.weatherConditions(location);

        return make_tuple(get<0>(wwapi), get<1>(rtw), get<1>(free));
    }
private:
    WorldWeatherAPI m_wwapi;
    FreeWeather m_free;
    RealtimeWeatherService m_rtw;
};

int main()
{
    // WorldWeatherAPI worldWeather;
    // FreeWeather freeWeather;
    // RealtimeWeatherService realtimeWeather;

    // auto const location = "San Francisco, CA, US";
    // // Call each API and combine the results
    // tuple<float, float, string> worldWeatherResult = worldWeather.getWeather(location);
    // tuple<float, string> freeWeatherResult = freeWeather.retrieve_weather(location);
    // tuple<float, float, string> realtimeWeatherResult = realtimeWeather.weatherConditions(location);

    // // Combine the results into a single string
    // float temperature = get<0>(worldWeatherResult);
    // float humidity = get<1>(realtimeWeatherResult);
    // string shortDescription = get<1>(freeWeatherResult);

    WeatherFacade wf;

    auto const location = "San Francisco, CA, US";

    tuple<float, float, string> currentWeather = wf.currentWeather(location);

    cout << "\nWeather for " << location << endl
         << get<2>(currentWeather) << endl
         << "Temperature: " << get<1>(currentWeather) << " C" << endl
         << "Humidity: " << get<0>(currentWeather) << " %" << endl;

    return 0;
}
