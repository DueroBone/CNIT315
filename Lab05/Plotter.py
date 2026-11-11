import matplotlib.pyplot as plt
import pandas as pd
import sys

# Read the data into a pandas DataFrame
df = pd.read_csv(sys.stdin)

print(df) # Re-print the DataFrame

# Plot data
plt.figure(figsize=(12, 8))
for column in df.columns[1:]:
    plt.plot(df["Size"], df[column], marker="o", label=column)

# Setup display
plt.xlabel("Array Size")
plt.ylabel("Time (seconds)")
plt.title("Performance of Sorting and Searching Algorithms")
plt.grid(True)
plt.legend()

plt.savefig("algorithm_performance_linear.png", dpi=300)  # Save the figure as a PNG file
plt.xscale("log")
plt.yscale("log")
plt.savefig("algorithm_performance.png", dpi=300)  # Save the figure as a PNG file
# plt.show()  # Show the plot fails due to linux