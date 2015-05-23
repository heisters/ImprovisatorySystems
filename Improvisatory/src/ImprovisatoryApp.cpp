#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "OscSender.h"
#include "OscListener.h"

class ImprovisatoryApp : public ci::app::App {
public:
    ImprovisatoryApp();

	void setup() override;
    void mouseDown( ci::app::MouseEvent event ) override;
	void update() override;
	void draw() override;

private:
    void                onOSCMessageReceived( const ci::osc::Message * msg );

    ci::osc::Sender     mSender;
    ci::osc::Listener   mListener;
};


using namespace ci;
using namespace ci::app;
using namespace std;

ImprovisatoryApp::ImprovisatoryApp()
{

}

void ImprovisatoryApp::setup()
{
    ci::log::manager()->enableConsoleLogging();


    mSender.setup( "10.2.0.255", 4000, true );
    mListener.setup( 4000 );
    mListener.registerMessageReceived( bind( &ImprovisatoryApp::onOSCMessageReceived, this, placeholders::_1 ) );
}

void ImprovisatoryApp::mouseDown( MouseEvent event )
{
}

void ImprovisatoryApp::update()
{
    osc::Message msg;
    msg.setAddress( "/master/time" );
    msg.addFloatArg( getElapsedSeconds() );
    mSender.sendMessage( msg );
}

void ImprovisatoryApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}


void ImprovisatoryApp::onOSCMessageReceived( const ci::osc::Message * msg )
{
    stringstream ss;
    ss << msg->getAddress();

    for ( int i = 0; i < msg->getNumArgs(); ++i )
    {
        switch ( msg->getArgType( i ) ) {
            case osc::TYPE_FLOAT:
                ss << " f " << msg->getArgAsFloat( i );
                break;
            case osc::TYPE_INT32:
                ss << " i " << msg->getArgAsInt32( i );
                break;
            case osc::TYPE_STRING:
                ss << " s " << msg->getArgAsString( i );
                break;

            default:
                break;
        }
    }

    CI_LOG_V( ss.str() );
}

CINDER_APP( ImprovisatoryApp, RendererGl )
