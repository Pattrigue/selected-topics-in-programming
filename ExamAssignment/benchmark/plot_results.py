import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import matplotlib.colors as mcolors
import argparse
import numpy as np

# Python script used to plot the benchmark results.

def plot_data(df, show_sync):
	colors = ['#E91E63', '#4CAF50', '#2196F3', '#FFC107', '#9C27B0', '#FF5722']

	plt.figure(figsize=(10,6))

	# Replace 'OS' in 'Thread count' column with a unique numeric identifier
	df['Thread count'] = df['Thread count'].replace('OS', -1)

	# Convert 'Thread count' column to numeric
	df['Thread count'] = pd.to_numeric(df['Thread count'])

	# Filter data
	single_threaded = df[(df['Thread count'] == 0) & (df['Benchmark'].str.contains('Synchronous'))]
	os_managed = df[(df['Thread count'] == -1) & (df['Benchmark'].str.contains('AndThreads'))]
	multithreaded = df[(df['Thread count'] > 0) & (df['Benchmark'].str.contains('AndThreads'))]

	if show_sync:
		plt.plot(single_threaded['Simulation count'], single_threaded['Time (ms)'], marker='o', linestyle='-', color=colors[0], label='Single-threaded')

	plt.plot(os_managed['Simulation count'], os_managed['Time (ms)'], marker='o', linestyle='-', color=colors[1], label='OS Managed')

	# Loop through the unique thread counts and create a plot for each
	for idx, thread_count in enumerate(multithreaded['Thread count'].unique(), start=2):
		subset = multithreaded[multithreaded['Thread count'] == thread_count]
		plt.plot(subset['Simulation count'], subset['Time (ms)'], marker='o', linestyle='-', color=colors[idx % len(colors)], label=f'Multithreaded ({thread_count} threads)')

	# Configure plot
	plt.xlabel('Simulation Count')
	plt.ylabel('Time (ms)')
	plt.title('Benchmark Results')
	plt.legend()
	plt.grid(True)
	plt.xticks(df['Simulation count'].unique())

	# Save the plot
	file_name = 'multithread_benchmark_with_sync.png' if show_sync else 'multithread_benchmark_without_sync.png'
	plt.savefig(file_name, dpi=300)
	plt.show()



def main(show_sync):
	df = pd.read_csv('results.csv')
	plot_data(df, show_sync)

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description='Plot benchmark data.')
	parser.add_argument('--show_sync', action='store_true', help='Include the single-threaded data in the plot')
	args = parser.parse_args()
	main(args.show_sync)
