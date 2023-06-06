import pandas as pd
import matplotlib.pyplot as plt
import glob

"""
This Python script plots the simulation results from the CSV files in the current directory.
Fulfills requirement 6:
"Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize".
"""

# Define data transformations in a dictionary
transformations = {
    'seihr.csv': {'column': 'H', 'transform': lambda x: x * 1000, 'note': '* 1000'}
}

# Get all CSV files in the current directory
csv_files = glob.glob('*.csv')

for file in csv_files:
    data = pd.read_csv(file)

    # Strip leading and trailing spaces from column names
    data.columns = data.columns.str.strip()
    data['Time'] = data['Time'].astype(float)

    # Check if there are transformations defined for this file
    if file in transformations:
        # Get the transformation parameters
        column_name = transformations[file]['column']
        transform_func = transformations[file]['transform']
        transform_note = transformations[file]['note']

        # Apply the transformation
        if column_name in data.columns:
            data[column_name] = data[column_name].apply(transform_func)
            # Rename the column to include the transformation note
            data.rename(columns={column_name: f'{column_name} {transform_note}'}, inplace=True)

    # Plot the data
    plt.figure(figsize=(10,6))

    for column in data.columns:
        if column != 'Time':
            plt.plot(data['Time'], data[column], label=column)

    plt.xlabel('Time')
    plt.ylabel('Quantity')
    plt.legend()

    # Save the figure to a PNG file
    plt.savefig(file.replace('.csv', '.png'), dpi=300)
    plt.close()
