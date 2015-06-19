#include <stdio.h>
#include <stdbool.h>

#include "sol-flow.h"
#include "sol-flow-static.h"
#include "sol-mainloop.h"

/* Soletta BUG: Should be included automatically */
#include "gpio-gen.h"

static struct sol_timeout *timeout_1seg;
static struct sol_flow_node *flow;

static const struct sol_flow_node_type *
create_0_root_type(void)
{
  static const struct sol_flow_node_type_gpio_reader_options opts0 =
  SOL_FLOW_NODE_TYPE_GPIO_READER_OPTIONS_DEFAULTS(
    .pin = { .val = 16, },
    .edge_falling = true,
    .edge_rising = true,
  );

  static const struct sol_flow_node_type_gpio_writer_options opts1 =
  SOL_FLOW_NODE_TYPE_GPIO_WRITER_OPTIONS_DEFAULTS(
    .pin = { .val = 15, },
  );

  static const struct sol_flow_static_conn_spec conns[] = {
    { 0, 0, 1, 0 },
    SOL_FLOW_STATIC_CONN_SPEC_GUARD
  };

  static struct sol_flow_static_node_spec nodes[] = {
    [0] = { NULL, "button", (struct sol_flow_node_options *) &opts0 },
    [1] = { NULL, "led", (struct sol_flow_node_options *) &opts1 },
    SOL_FLOW_STATIC_NODE_SPEC_GUARD
  };

  struct sol_flow_static_spec spec = {
    .api_version = 1,
    .nodes = nodes,
    .conns = conns,
    .exported_in = NULL,
    .exported_out =
    NULL,
  };

  nodes[0].type = SOL_FLOW_NODE_TYPE_GPIO_READER;
  nodes[1].type = SOL_FLOW_NODE_TYPE_GPIO_WRITER;

  return sol_flow_static_new_type(&spec);
}

static bool
timeout_1seg_cb(void *data)
{
  printf("1seg\n");
  return true;
}

static void
startup(void)
{
  const struct sol_flow_node_type *type;

  type = create_0_root_type();
  if(!type) return;

  flow = sol_flow_node_new(NULL, NULL, type, NULL);
  timeout_1seg = sol_timeout_add(1000, timeout_1seg_cb, NULL);
}

static void
shutdown(void)
{
  sol_timeout_del(timeout_1seg);
  sol_flow_node_del(flow);
}

SOL_MAIN_DEFAULT(startup, shutdown)
