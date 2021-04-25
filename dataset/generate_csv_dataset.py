import csv
import random


def csv_writer(k, path):
    """
    Write data to a CSV file path
    """
    with open(path, "w", newline='') as csv_file:
        writer = csv.writer(csv_file, delimiter=',')
        data = []
        for line in range(k):
            data.append(random.randrange(1, k))
            writer.writerow(data)
            data = []


if __name__ == "__main__":
    amount = [100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000]
    for i in range(10):
        for j in range(10):
            path = "data" + "0" + str(i + 1) + "/" + str(amount[j]) + ".csv"
            csv_writer(amount[j], path)