#ifndef GAZEBO_PHYSICS_PLUGIN_HH
#define GAZEBO_PHYSICS_PLUGIN_HH

#include <string>

// Custom Callback Queue
#include <ros/callback_queue.h>
#include <ros/subscribe_options.h>
#include <ros/advertise_options.h>

#include <ros/ros.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#include <gazebo/physics/physics.hh>
#include <gazebo/transport/TransportTypes.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/Events.hh>

#include "gazebo_ext_msgs/GetSurfaceParams.h"
#include "gazebo_ext_msgs/SetSurfaceParams.h"

namespace gazebo
{

class GazeboPhysicsPlugin : public WorldPlugin
{
  /// \brief Constructor
  public: GazeboPhysicsPlugin();

  /// \brief Destructor
  public: virtual ~GazeboPhysicsPlugin();

  // Documentation inherited
  protected: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf);

  // Documentation inherited
  protected: virtual void UpdateChild();

  /// \brief A pointer to the gazebo model.
  private: physics::WorldPtr world_;

  /// \brief A pointer to the ROS node.  A node will be instantiated if it does not exist.
  private: ros::NodeHandle* rosnode_;

  /// \brief A mutex to lock access to fields that are used in ROS message callbacks
  private: boost::mutex lock_;

  private: ros::ServiceServer get_srv_;
  private: ros::ServiceServer set_srv_;
  private: bool GetSurfaceParamsCallback(gazebo_ext_msgs::GetSurfaceParams::Request &req,
                                         gazebo_ext_msgs::GetSurfaceParams::Response &res);
  private: bool SetSurfaceParamsCallback(gazebo_ext_msgs::SetSurfaceParams::Request &req,
                                         gazebo_ext_msgs::SetSurfaceParams::Response &res);

  // Custom Callback Queue
  private: ros::CallbackQueue queue_;
  private: void QueueThread();
  private: boost::thread callback_queue_thread_;
};
}
#endif