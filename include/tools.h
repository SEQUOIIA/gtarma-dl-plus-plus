#include <cpr\cpr.h>
#include <rapidjson\document.h>
#include <vector>
#include <curl\curl.h>
#include <sstream>

#include "models.h"


namespace gtarma {

	const char *ENDPOINT_DRIVEFILES = "https://clients6.google.com/drive/v2beta/files";
	const char *ENDPOINT_DRIVEDLFILE = "https://drive.google.com/uc";
	const char *REFERER = "https://drive.google.com/drive/folders/0B8j-xMQtDZvwVjN6R25sWF94dG8";
	const char *KEY = "AIzaSyC1qbk75NzWBvSaDh6KnsjjA9pIrP4lYIE";
	const char *Q = "trashed = false and '0B8j-xMQtDZvwVjN6R25sWF94dG8' in parents";

	std::vector<model::Item> GetFiles() {
		cpr::Response resp = cpr::Get(cpr::Url{ ENDPOINT_DRIVEFILES },
			cpr::Header{
				{ "Referer", REFERER }
		},
			cpr::Parameters{
				{ "openDrive", "true" },
				{ "reason", "102" },
				{ "syncType", "0" },
				{ "errorRecovery", "false" },
				{ "fields", "kind,nextPageToken,items(kind,title,mimeType,createdDate,modifiedDate,modifiedByMeDate,lastViewedByMeDate,fileSize,owners(kind,permissionId,displayName,picture),lastModifyingUser(kind,permissionId,displayName,picture),hasThumbnail,thumbnailVersion,iconLink,id,shared,sharedWithMeDate,userPermission(role),explicitlyTrashed,quotaBytesUsed,shareable,copyable,fileExtension,sharingUser(kind,permissionId,displayName,picture),spaces,editable,version,teamDriveId,hasAugmentedPermissions,trashingUser(kind,permissionId,displayName,picture),trashedDate,parents(id),labels(starred,hidden,trashed,restricted,viewed),capabilities(canCopy,canDownload,canEdit,canAddChildren,canDelete,canRemoveChildren,canShare,canTrash,canRename,canReadTeamDrive,canMoveTeamDriveItem)),incompleteSearch" },
				{ "appDataFilter", "NO_APP_DATA" },
				{ "spaces", "drive" },
				{ "maxResults", "50" },
				{ "orderBy", "folder,title_natural asc" },
				{ "key", KEY },
				{ "q", Q }
		}
		);

		//std::cout << resp.status_code << '\n' << resp.text;

		rapidjson::Document doc;

		doc.Parse(resp.text.c_str());

		rapidjson::Value& items = doc["items"];
		int count = 0;
		std::vector<model::Item> payloadv;
		for (rapidjson::Value::ConstValueIterator i = items.Begin(); i != items.End(); i++) 
		{
			rapidjson::Value& item = items[count];
			model::Item payload;

			rapidjson::Value& id = item["id"];
			rapidjson::Value& filename = item["title"];

			payload.Id = id.GetString();
			payload.Filename = filename.GetString();

			payloadv.push_back(payload);

			count++;
		}

		return payloadv;
	}

	size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
	{
		size_t written;
		written = fwrite(ptr, size, nmemb, stream);
		return written;
	}

	void DownloadFile(model::Item item) {
		CURL *curl;
		FILE *fp;
		CURLcode res;
		curl = curl_easy_init();
		std::stringstream urlstream; urlstream
			<< ENDPOINT_DRIVEDLFILE << "?authuser=0&export=download&id=" << curl_easy_escape(curl, item.Id.c_str(), item.Id.size());
		std::cout << urlstream.str() << '\n';

		char *url = new char[urlstream.str().length() + 1];
		strcpy(url, urlstream.str().c_str());

		char const* outfilename = item.Filename.c_str();
		if (curl)
		{
			fp = fopen(outfilename, "wb");
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
			curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 1024000L);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			fclose(fp);
		}
	}
}