import csv

requirements = []
for security in securities:
    requirements.append(calculate_15c3_1(security))

total_long_pos = 0
total_short_pos = 0

with open('output.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['ITEMA', 'TICKER', 'CONTRACT DETAILS', 'POSITION (LONG/SHORT)', 'QUANTITY', 'PRICE', 'CASH ALLOCATION', 'SEA Rule 15c3-1 NET CAPITAL REQUIREMENT'])
    for i, security in enumerate(securities):
        writer.writerow([f'ITEM{i+1}', security['ticker'], f"{security['coupon']}% {security['maturity_year']} {security['grade']}", security['intent'].upper(), security['quantity'], get_price(security), calculate_cash_allocation(security), requirements[i]])

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv('stock_prices.csv')

weights = np.array([0.2, 0.3, 0.5])
rfr = 0.02

log_returns = np.log(df[['AAPL', 'GOOG', 'AMZN']].pct_change() + 1)

mu = log_returns.mean()
cov = log_returns.cov()

num_simulations = 1000
time_horizon = 252

simulations = np.random.multivariate_normal(mu, cov, num_simulations * time_horizon)

prices = np.zeros_like(simulations)
prices[0] = df.iloc[-1].values

for i in range(1, time_horizon):
    prices[i] = prices[i - 1] * np.exp(simulations[i])

portfolio_values = np.dot(prices, weights)

daily_returns = portfolio_values[1:] / portfolio_values[:-1] - 1

var = np.percentile(daily_returns, 1)

es = np.mean(daily_returns[daily_returns <= var])

expected_return = np.exp(np.sum(mu * weights) * time_horizon) - 1
std_dev = np.sqrt(np.dot(weights.T, np.dot(cov, weights))) * np.sqrt(time_horizon)

print(f"Expected Return: {expected_return:.2%}")
print(f"Standard Deviation: {std_dev:.2%}")
print(f"VaR (1%): {var:.2%}")
print(f"Expected Shortfall: {es:.2%}")

plt.hist(daily_returns, bins=50)
plt.title('Daily Returns Histogram')
plt.xlabel('Daily Returns')
plt.ylabel('Frequency')
plt.show()