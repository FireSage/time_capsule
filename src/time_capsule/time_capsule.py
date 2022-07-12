import subprocess


def run(command):
	result = subprocess.run(["powershell", "-Command", command], capture_output=True,text=True)
	return result

def get_processes():
	command = "(Get-Process | Select MainWindowTitle,ProcessName,Id | where{$_.MainWindowTitle -ne \"\"} | ConvertTo-Csv -Delimiter '|') -replace '\"',''"

	processes = run(command)

	# TODO: Error handling - use try block - check for error in execution
	# print(type(processes))
	# TODO: extract process data from string 
	res = processes.stdout.split("\n")
	res_clean = []
	for re in res:
		split_re = re.split("|")
		if len(split_re) == 3 and split_re[2] != 'Id':
			res_clean.append(split_re)

print(res_clean)