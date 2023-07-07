import os
import shutil
from typing import List, Union


def getFilenames(root_directory : str, queries : Union[list,str] = '.tif'):
    """Given directory with datafiles, get just imagefilenames

    :param root_directory: root search directory.  Function will traverse subdirectories for image files, 
        so ideally if you only want images within the same level of directory, don't use this function
    :type root_directory: str

    :param queries: strings to look for in the filename
    :type queries: str, List[str]

    :rtype: List[str]
        a list of file paths to files that match that of the regex query
    """
    img_filelist = []
    for current_location, sub_directories, files in os.walk(root_directory):
        if files:
            for img_file in files:
                if isinstance(queries, str):
                    if (queries.lower() in img_file.lower()) and '_thumb_' not in img_file:
                        img_filelist.append(os.path.join(current_location, img_file))
                elif isinstance(queries, list):
                    if all(query.lower() in img_file.lower() for query in queries) and '_thumb_' not in img_file:
                        img_filelist.append(os.path.join(current_location, img_file))
    img_filelist.sort()
    return img_filelist
