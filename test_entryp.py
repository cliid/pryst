# This script is needed for subprocess launched during tests;
# this way subprocess will not use pryst package from the site-packages directory
from pryst.prystapp import main
if __name__ == '__main__':
    main()
