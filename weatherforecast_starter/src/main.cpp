/*
Assignment 4: Weather Forecast

This assignment works with template functions and lambdas to become the best
weather forecaster at the Stanford Daily. Be sure to read the assignment details
in the PDF.

Submit to Paperless by 11:59pm on 2/16/2024.
*/

// TODO: import anything from the STL that might be useful!
#include <algorithm>
#include <concepts>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <vector>

// TODO: write convert_f_to_c function here. Remember it must be a template
// function that always returns a double.
template <typename Type>
concept Numerical = std::is_arithmetic_v<Type>;
template <Numerical Type> double convert_f_to_c(Type temp) {
  return (static_cast<double>(temp) - 32) * 5.0 / 9.0;
}
template <typename Function>
std::vector<double> get_forecast(std::vector<std::vector<double>> readings,
                                 Function fn) {
  // TODO: write get_forecast here!
  std::vector<double> forecast;
  forecast.reserve(readings.size());
for (auto const &day : readings) {
    forecast.push_back(fn(day));
  }
  return forecast;
}

int main() {
  std::vector<std::vector<int>> readings = {
      {70, 75, 80, 85, 90}, {60, 65, 70, 75, 80}, {50, 55, 60, 65, 70},
      {40, 45, 50, 55, 60}, {30, 35, 40, 45, 50}, {50, 55, 61, 65, 70},
      {40, 45, 50, 55, 60}};

  // TODO: Convert temperatures to Celsius and output to output.txt
  std::vector<std::vector<double>> celsius_readings(readings.size());
  for (auto i = 0; i < readings.size(); ++i) {
    std::transform(readings[i].begin(), readings[i].end(),
                   std::back_inserter(celsius_readings[i]),
                   [](const int& temp) { return convert_f_to_c(temp); });
  }
  std::ofstream output("output.txt");
  for (auto const &day : celsius_readings) {
    for (auto const &temp : day) {
      output << temp << " ";
    }
    output << "\n";
  }
  output << std::endl;

  // TODO: Find the maximum temperature for each day and output to output.txt
  std::vector<double> const max_temps =
      get_forecast(celsius_readings, [](const std::vector<double> &day) {
        return *std::max_element(day.begin(), day.end());
      });
  for (auto const &temp : max_temps) {
    output << temp << " ";
  }
  output << "\n" << std::endl;

  // TODO: Find the minimum temperature for each day and output to output.txt
  std::vector<double> const min_temps =
      get_forecast(celsius_readings, [](const std::vector<double> &day) {
        return *std::min_element(day.begin(), day.end());
      });
  for (auto const &temp : min_temps) {
    output << temp << " ";
  }
  output << "\n" << std::endl;

  // TODO: Find the average temperature for each day and output to output.txt
  std::vector<double> const avg_temps =
      get_forecast(celsius_readings, [](const std::vector<double> &day) {
        return std::accumulate(day.begin(), day.end(), 0.0) /
               static_cast<double>(day.size());
      });
  for (auto const &temp : avg_temps) {
    output << temp << " ";
  }
  output << "\n" << std::endl;

  output.close();

  return 0;
}