#include <cpr\cpr.h>
#include <iostream>


int main() {

	const char *ENDPOINT_DRIVEFILES = "https://clients6.google.com/drive/v2beta/files";
	const char *REFERER = "https://drive.google.com/drive/folders/0B8j-xMQtDZvwVjN6R25sWF94dG8";
	const char *KEY = "AIzaSyC1qbk75NzWBvSaDh6KnsjjA9pIrP4lYIE";
	const char *Q = "trashed = false and '0B8j-xMQtDZvwVjN6R25sWF94dG8' in parents";

	cpr::Response resp = cpr::Get(cpr::Url{ENDPOINT_DRIVEFILES},
		cpr::Header{ 
			{"Referer", REFERER} 
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
			{ "q", Q}
		}
	);

	std::cout << resp.status_code << '\n' << resp.text;

	return 1;
}