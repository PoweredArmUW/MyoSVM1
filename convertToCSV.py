import numpy
import csv

def npyToCSV(name):
    npyname = name + '.npy'
    csvname = name + '.csv'
    array = numpy.load(npyname)
    with open(csvname, 'w') as csvfile:
        writer = csv.writer(csvfile);
        writer.writerow([len(array), len(array[0])])
        writer.writerows(array)

npyToCSV('data/emg_unprocessed')
npyToCSV('data/last_third')
npyToCSV('data/first_third')