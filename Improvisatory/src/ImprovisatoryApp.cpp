#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImprovisatoryApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void ImprovisatoryApp::setup()
{
}

void ImprovisatoryApp::mouseDown( MouseEvent event )
{
}

void ImprovisatoryApp::update()
{
}

void ImprovisatoryApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( ImprovisatoryApp, RendererGl )
