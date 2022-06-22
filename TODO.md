This TODO list is automatically generated from the cookiecutter-cpp-project template.
The following tasks need to be done to get a fully working project:


* Push to your remote repository for the first time by doing `git push origin main`.
* Make sure that the following software is installed on your computer:
  * A C++-17-compliant C++ compiler
  * CMake `>= 3.9`
* Make sure that CI/CD pipelines are enabled in your Gitlab project settings and that
  there is a suitable Runner available. If you are using the cloud-hosted gitlab.com,
  this should already be taken care of.
* Enable the integration with `codecov.io` by heading to the [Codecov.io Website](https://codecov.io),
  log in (e.g. with your Github credentials) and enable integration for your repository. This will
  allow you to have automatic coverage reports on pull requests, but is not necessary to display
  the coverage badge in the README.
* Enable the integration with `sonarcloud.io` by heading to the [Sonarcloud.io Website](https://sonarcloud.io),
  log in (e.g. with your Github credentials), add the repository and select *Github Actions* as the
  preferred method of integration. Follow step 1 and set up the secret variable `SONAR_TOKEN`. Step 2
  and 3 are already taken care of by this cookiecutter. In order to have the SonarCloud badge in the
  README show something meaningful, a *New Code Definition* needs to be configured in Sonarcloud under
  *Administration/New Code*.