



//equal=0为>=,equal=1为>
int getAfterStatus(vector<string> &full_vec, int equal, char *status, vector<string> &after_vec)
{
	int ifail = 0, i = 0, j = 0;
	logical flag = false;
	for (i = 0; i < full_vec.size(); i++)
	{
		if (stricmp(full_vec[i].c_str(), status) == 0)
		{
			flag = true;
			break;
		}

	}
	if (flag)
	{
		if (equal == 0)
		{
			for (j = i; j < full_vec.size(); j++)
			{
				ECHO("起始:%d, full_vec[%d]:%s\n", i, j, full_vec[j].c_str());
				after_vec.push_back(full_vec[j]);

			}
		}
		else if (equal == 1)
		{
			for (j = i + 1; j < full_vec.size(); j++)
			{
				ECHO("起始:%d, full_vec[%d]:%s\n", i, j, full_vec[j].c_str());
				after_vec.push_back(full_vec[j]);

			}
		}
	}
	return ifail;
}

logical isInVec(vector<string> &full_vec, char *arg_status, int equal, char *status)
{
	int ifail = 0, i = 0, j = 0;
	logical isInclude = false;
	vector<string> after_vec;

	getAfterStatus(full_vec, equal, arg_status, after_vec);
	for (i = 0; i < after_vec.size(); i++)
	{
		ECHO("after_vec[%d]:%s status:%s\n", i, after_vec[i].c_str(), status);
		if (stricmp(after_vec[i].c_str(), status) == 0)
		{
			isInclude = true;
			break;
		}
	}
	return isInclude;
}


