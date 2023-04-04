#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class MACD
{
private:
    struct Day
    {
    public:
        std::string Date;
        double AvgPrice;
        Day() = default;
        Day(std::string date, double avgPrice)
            :Date(date),AvgPrice(avgPrice) {}
    };

    std::vector<MACD::Day> m_PricesData;
    std::vector<double> m_MACD;
    std::vector<double> m_Signal;
public:
    MACD()
    {
        m_MACD = std::vector<double>(26, 0);
        m_Signal = std::vector<double>(35, 0);
        ParseInputFile("EtheriumPrices.txt");
        GenerateMACD();
        GenerateSignal();
        CreateOutputFiles();
    }

    double CalculateProfit()
    {
        constexpr double InitialBudget = 1000.0;
        double TotalBudget = InitialBudget;
        double CurrentEtheriumWalet = 0.0;
        for (int i = 36; i < 1000; i++)
        {
            if (m_Signal[i - 1] > m_MACD[i - 1] && m_Signal[i] < m_MACD[i])
            {
                CurrentEtheriumWalet = TotalBudget / m_PricesData[i].AvgPrice;
                TotalBudget = 0.0;
            }
            else if (m_Signal[i - 1] < m_MACD[i - 1] && m_Signal[i] > m_MACD[i])
            {
                TotalBudget += m_PricesData[i].AvgPrice * CurrentEtheriumWalet;
                CurrentEtheriumWalet = 0.0;
            }
        }

        return TotalBudget - InitialBudget;
    }

private:
    void GenerateMACD()
    {
        for (int i = 26; i < m_PricesData.size(); i++)
        {
            m_MACD.push_back(CalculateEMA(i, 12, true) - CalculateEMA(i, 26, true));
        }
    }

    void GenerateSignal()
    {
        for (int i = 35; i < m_MACD.size(); i++)
        {
            m_Signal.push_back(CalculateEMA(i, 9, false));
        }
    }

    double CalculateEMA(uint16_t startintPoint, uint16_t period, bool usePrices)
    {
        double Nominator = 0;
        double Denominator = 0;
        const double Alpha = 2.0 / (period + 1);

        for (int i = startintPoint-period; i < startintPoint; i++)
        {
            Nominator += (usePrices ? m_PricesData[i].AvgPrice : m_MACD[i]) * std::pow((1 - Alpha), i);
            Denominator += std::pow((1 - Alpha), i);
        }
        return Nominator / Denominator;
    }

    void ParseInputFile(const std::string& path)
    {
        std::ifstream in(path);
        std::string Date, Open, High, Low;

        while (in.good())
        {
            in >> Date >> Open >> High >> Low;
            Day day(Date, (double)((std::stoi(High) + (std::stoi(Low)) / 2)));
            m_PricesData.push_back(day);
        }
        in.close();
       
    }

    void CreateOutputFiles()
    {
        std::ofstream out("MACD_Signal_Values.txt");
        for (int i = 0; i < 1000; i++)
        {
            out << m_PricesData[i].Date << " " << m_MACD[i] << " " << m_Signal[i] << std::endl;                        
        }
        out.close();
        out.open("Etherium_Values.txt");
        for (int i = 0; i < 1000; i++)
        {
            out << m_PricesData[i].AvgPrice << std::endl;
        }
        out.close();
    }
};

int main()
{
    MACD m = MACD();
    std::cout << m.CalculateProfit();
    return 0;
}
